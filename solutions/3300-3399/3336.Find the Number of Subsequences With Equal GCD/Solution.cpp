// 题目：3336. 最大公约数相等的子序列数量（Find the Number of Subsequences With Equal GCD）
// 思路：记忆化搜索 dfs(i, j, k)，表示考虑前 i 个元素、两个子序列当前 GCD 分别为 j、k 时的方案数；每个元素有三种去向（都不放、放第一个、放第二个），i < 0 时 j == k 才合法。
// 时间复杂度：O(n·m^2·log V)，m = max(nums)；空间复杂度：O(n·m^2)，记忆化表大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int subsequencePairCount(vector<int>& nums) {  // nums 是输入数组；返回两个非空子序列 GCD 相等的方案数
        const int MOD = 1e9 + 7;  // 取模常量
        int n = nums.size();  // 元素个数
        int m = ranges::max(nums);  // 数组最大值，作为 GCD 状态的上界（GCD 不会超过最大值）
        vector f(n, vector(m + 1, vector<int>(m + 1, -1)));  // 记忆化数组 f[i][j][k]，-1 表示该状态还没计算过
        auto dfs = [&](this auto&& dfs, int i, int j, int k) -> int {  // 递归 lambda：i 是当前下标，j、k 是两个子序列当前的 GCD
            if (i < 0) {  // i < 0 表示所有元素都已决策完毕
                return j == k;  // 两个子序列的 GCD 相等才算一种合法方案
            }  // 递归出口结束
            int& res = f[i][j][k];  // 用引用拿到记忆化格子，写它就等于写回缓存
            if (res < 0) {  // 只计算一次，重复访问直接复用缓存
                res = ((dfs(i - 1, j, k)  // 第一种去向：第 i 个数不放进任何子序列
                           + dfs(i - 1, gcd(nums[i], j), k))  // 第二种去向：放进第一个子序列，GCD 与 nums[i] 合并
                              % MOD  // 前两项之和先取模，避免相加溢出
                          + dfs(i - 1, j, gcd(nums[i], k)))  // 第三种去向：放进第二个子序列
                    % MOD;  // 三项求和后再取模
            }  // 缓存判断结束
            return res;  // 返回记忆化结果
        };  // 递归 lambda 结束
        return (dfs(n - 1, 0, 0) - 1 + MOD) % MOD;  // 减 1 去掉两个子序列都为空的情况，加 MOD 防止负数
    }  // 方法结束
};  // 类定义结束