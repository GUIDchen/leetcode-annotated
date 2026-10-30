# 题目：3082. 求出所有子序列的能量和（Find the Sum of the Power of All Subsequences）
# 思路：背包计数 DP，f[i][j] 表示前 i 个数中被标记出的子序列和为 j 的方案数；不选当前数时方案数翻倍，选它则由 j - x 转移。
# 时间复杂度：O(n·k)；空间复杂度：O(n·k)，滚动数组可降到 O(k)。
class Solution:  # LeetCode 约定的题解类
    def sumOfPower(self, nums: List[int], k: int) -> int:  # nums：原数组；k：目标和；返回所有子序列的能量和（模 1e9+7）
        mod = 10**9 + 7  # 取模常量
        n = len(nums)  # 数组长度
        f = [[0] * (k + 1) for _ in range(n + 1)]  # f[i][j]：前 i 个元素中，被标记出的子序列和为 j 的方案数
        f[0][0] = 1  # 空集和为 0，方案数为 1
        for i, x in enumerate(nums, 1):  # 从 1 开始编号，x 是第 i 个元素
            for j in range(k + 1):  # 枚举被标记子序列的和 j
                f[i][j] = f[i - 1][j] * 2 % mod  # 不选 x：和不变，而 x 可自由地不被标记，所以方案数翻倍
                if j >= x:  # 和足够大时才可能选上 x
                    f[i][j] = (f[i][j] + f[i - 1][j - x]) % mod  # 选 x：累加「和减少 x」的方案数
        return f[n][k]  # 前 n 个元素中和为 k 的方案数即为答案
