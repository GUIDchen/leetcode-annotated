// 题目：813. 最大平均值和的分组（Largest Sum of Averages）
// 思路：前缀和求任意区间和，记忆化搜索枚举第一段的切分点，把「分成 k 段」化归为「剩余部分分成 k-1 段」。
// 时间复杂度：O(k * n^2)；空间复杂度：O(k * n)，记忆化数组保存全部状态。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double largestSumOfAverages(vector<int>& nums, int k) {  // nums 为数组，k 为最多划分的段数
        int n = nums.size();  // n 是数组长度
        int s[n + 1];  // 前缀和数组，s[i] 表示前 i 个元素之和
        double f[n][k + 1];  // 记忆化数组 f[i][k]：从下标 i 开始分成 k 段能得到的最大平均值和
        memset(f, 0, sizeof(f));  // 全部清零，同时把 0 当作「该状态尚未计算」的标记
        s[0] = 0;  // 前缀和边界：前 0 个元素之和为 0
        for (int i = 0; i < n; ++i) {  // 递推前缀和
            s[i + 1] = s[i] + nums[i];  // s[i + 1] 等于前 i 项之和再加上 nums[i]
        }  // 前缀和计算结束
        auto dfs = [&](this auto&& dfs, int i, int k) -> double {  // 记忆化搜索：this auto 让 lambda 能递归调用自身
            if (i == n) {  // 元素已经用完，没有可以再分的段
                return 0;  // 该状态的贡献为 0
            }  // if 结束
            if (k == 1) {  // 只剩一段，剩下的元素必须全部归为这一段
                return (s[n] - s[i]) * 1.0 / (n - i);  // 剩余区间的平均值
            }  // if 结束
            if (f[i][k] > 0) {  // 已经计算过就直接复用
                return f[i][k];  // 返回记忆化结果
            }  // if 结束
            double ans = 0;  // 本状态的最优值，初值为 0
            for (int j = i + 1; j < n; ++j) {  // 第一段是 [i, j)，从 j 开始还要再分 k-1 段
                ans = max(ans, (s[j] - s[i]) * 1.0 / (j - i) + dfs(j, k - 1));  // 第一段平均值加上剩余部分的最优值
            }  // for 结束
            return f[i][k] = ans;  // 先写入记忆化数组，再返回该值
        };  // lambda 结束
        return dfs(0, k);  // 从下标 0 开始，把整个数组分成 k 段
    }  // 方法结束
};  // 类定义结束
