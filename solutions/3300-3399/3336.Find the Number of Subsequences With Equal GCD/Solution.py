# 题目：3336. 最大公约数相等的子序列数量（Find the Number of Subsequences With Equal GCD）
# 思路：记忆化搜索 dfs(i, j, k) 表示处理到第 i 个数、两个子序列当前 GCD 分别为 j、k 时的方案数；每个数有三种去向（都不放、放第一个、放第二个），i < 0 时 j == k 才合法，最后减去两个子序列都为空的一种。
# 时间复杂度：O(n·m^2·log V)，m = max(nums)；空间复杂度：O(n·m^2)，记忆化表大小。
class Solution:  # LeetCode 约定的题解类
    def subsequencePairCount(self, nums: List[int]) -> int:  # nums 是输入数组；返回两个非空子序列 GCD 相等的方案数
        @cache  # @cache 自动记忆化，同一组 (i, j, k) 只计算一次
        def dfs(i: int, j: int, k: int) -> int:  # 递归函数：i 是当前下标，j、k 是两个子序列当前的 GCD
            if i < 0:  # i < 0 表示所有元素都已决策完毕
                return int(j == k)  # 两个子序列的 GCD 相等才计数
            return (  # 三种转移：不选、放进第一个子序列、放进第二个子序列
                dfs(i - 1, j, k)  # 不选第 i 个数
                + dfs(i - 1, gcd(nums[i], j), k)  # 放进第一个子序列，GCD 与 nums[i] 合并
                + dfs(i - 1, j, gcd(nums[i], k))  # 放进第二个子序列
            ) % mod  # 三项求和后对 mod 取模

        mod = 10**9 + 7  # 取模常量
        return (dfs(len(nums) - 1, 0, 0) - 1) % mod  # 减 1 去掉两个子序列都为空的情况
