// 题目：1981. 最小化目标值与所选元素的差（Minimize the Difference Between Target and Chosen Elements）
// 思路：用布尔可达性数组做逐行背包，每行所有元素都允许重复选，把旧表整体右移 x 位与进新表，最后取与 target 差值最小的可达和。
// 时间复杂度：O(m·n·S)，S 为可能出现的最大和；空间复杂度：O(S)，两张滚动数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimizeTheDifference(vector<vector<int>>& mat, int target) {  // mat：m×n 矩阵；target：目标值，返回每行选一个数后与 target 的最小绝对差
        vector<int> f = {1};  // f[j] 表示「前若干行每行选一个数」能否凑出和 j，初始只有 0 可达
        for (auto& row : mat) {  // 逐行往下递推
            int mx = *max_element(row.begin(), row.end());  // 本行最大值，决定了新表和的最大上界
            vector<int> g(f.size() + mx);  // 新的可达性表，最大和最多在旧的基础上再增加 mx
            for (int x : row) {  // 枚举本行可以选中的元素 x
                for (int j = x; j < f.size() + x; ++j) {  // 把旧表整体右移 x 位写进 g，用拷贝而非原地更新，避免同一元素被重复使用
                    g[j] |= f[j - x];  // 若 j-x 可达，那么再加上 x 后 j 也可达（|= 支持多种选法共用同一个和）
                }  // x 循环结束
            }  // 元素枚举结束
            f = move(g);  // 用新表滚动替换旧表，move 省掉一次深拷贝
        }  // 行循环结束
        int ans = 1 << 30;  // 答案先设成一个足够大的数
        for (int j = 0; j < f.size(); ++j) {  // 扫描所有可能的和
            if (f[j]) {  // 该和确实可以由每行选一个数凑出来
                ans = min(ans, abs(j - target));  // 用与 target 的绝对差更新答案
            }  // 可达性判断结束
        }  // 扫描结束
        return ans;  // 返回最小绝对差
    }  // 方法结束
};  // 类定义结束