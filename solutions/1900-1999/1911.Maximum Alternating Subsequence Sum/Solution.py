# 题目：1911. 最大交替子序列和（Maximum Alternating Subsequence Sum）
# 思路：动态规划，g[i] 表示前 i 个数中最后取的元素作「加号位」的最大交替和，f[i] 表示最后取的元素作「减号位」的最大交替和，两者互相转移。
# 时间复杂度：O(n)，一次线性递推；空间复杂度：O(n)，两个长度为 n+1 的 DP 数组。
class Solution:  # LeetCode 约定的题解类
    def maxAlternatingSum(self, nums: List[int]) -> int:  # nums：输入整数数组，返回最大交替子序列和
        n = len(nums)  # n：数组长度，DP 数组多开一位作为下标 0 的边界
        f = [0] * (n + 1)  # f[i]：前 i 个数中、最后取的元素处于「减号位」时的最大交替和
        g = [0] * (n + 1)  # g[i]：前 i 个数中、最后取的元素处于「加号位」时的最大交替和，初值 0 表示空序列
        for i, x in enumerate(nums, 1):  # 从下标 1 开始枚举，enumerate 的起始值设为 1，x 为 nums[i-1]
            f[i] = max(g[i - 1] - x, f[i - 1])  # 要么接在 g[i-1] 后面减掉 x，要么跳过 x 沿用 f[i-1]
            g[i] = max(f[i - 1] + x, g[i - 1])  # 要么接在 f[i-1] 后面加上 x，要么跳过 x 沿用 g[i-1]
        return max(f[n], g[n])  # 两种结尾状态取较大值即为答案
