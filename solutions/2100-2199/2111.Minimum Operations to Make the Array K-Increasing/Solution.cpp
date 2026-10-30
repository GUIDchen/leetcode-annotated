// 题目：2111. 使数组 K 递增的最少操作次数（Minimum Operations to Make the Array K-Increasing）
// 思路：下标模 k 相同的元素互不影响，各自成一条子链；每条子链保留「最长非降子序列」不动，其余元素改成合适值即可。
// 时间复杂度：O(n log n)，每条子链用二分维护 LIS；空间复杂度：O(n)，辅助数组 t 存候选结尾。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int kIncreasing(vector<int>& arr, int k) {  // arr：原数组；k：要求满足 arr[i] <= arr[i+k] 的步长；返回最少操作次数
        int ans = 0, n = arr.size();  // ans 累计最少修改次数，n 为数组长度
        for (int i = 0; i < k; ++i) {  // 枚举 k 条独立子链的起点 i（0..k-1）
            vector<int> t;  // t 收集下标 i, i+k, i+2k, ... 这条子链上的全部元素
            for (int j = i; j < n; j += k) t.push_back(arr[j]);  // 按步长 k 抽取子链元素，子链之间彼此独立
            ans += lis(t);  // 把该子链需要的最少修改次数累加进答案
        }  // 起点枚举结束
        return ans;  // 返回全局最少操作次数
    }  // kIncreasing 方法结束

    int lis(vector<int>& arr) {  // 求「最长非降子序列」长度，并换算成需要修改的元素个数
        vector<int> t;  // t 是贪心数组：t[len-1] 表示长度为 len 的非降子序列的最小可能结尾
        for (int x : arr) {  // 依次把每个元素 x 作为新的候选结尾
            auto it = upper_bound(t.begin(), t.end(), x);  // 找第一个 > x 的位置（用 upper_bound 允许相等，对应「非降」）
            if (it == t.end())  // 没找到更大的结尾，说明 x 可以延长当前最长子序列
                t.push_back(x);  // 追加到尾部，LIS 长度 +1
            else  // 否则找到了可以替换的位置
                *it = x;  // 用更小的 x 替换该位置，给后续元素留下更优的结尾
        }  // 遍历结束，t.size() 就是 LIS 长度
        return arr.size() - t.size();  // 子链长度减去 LIS 长度，就是必须被修改的最少元素个数
    }  // lis 方法结束
};  // Solution 类定义结束