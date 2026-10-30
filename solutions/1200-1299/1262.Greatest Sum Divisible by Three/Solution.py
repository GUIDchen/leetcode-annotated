# 题目：1262. 可被三整除的最大和（Greatest Sum Divisible by Three）
# 思路：动态规划——f[i][j] 表示前 i 个数中选若干、和模 3 余 j 的最大和；对每个数做「不选 / 选」两种转移取较大值。
# 时间复杂度：O(n)，每个数只更新 3 个余数状态；空间复杂度：O(n)，使用 (n+1)×3 的 DP 表。
class Solution:  # LeetCode 约定的题解类
    def maxSumDivThree(self, nums: List[int]) -> int:  # nums 是正整数数组，返回能被 3 整除的最大子集和
        n = len(nums)  # n 为数组长度
        f = [[-inf] * 3 for _ in range(n + 1)]  # DP 表：f[i][j] 表示前 i 个数的子集和模 3 余 j 的最大值，初值 -inf 表示不可达
        f[0][0] = 0  # 空集的模 3 余数为 0，和为 0
        for i, x in enumerate(nums, 1):  # enumerate 从 1 开始编号，正好对应「前 i 个数」
            for j in range(3):  # 枚举目标余数 j
                f[i][j] = max(f[i - 1][j], f[i - 1][(j - x) % 3] + x)  # 在「不选 x」与「选 x」之间取较大值；Python 的 % 对负数也返回非负余数，故无需额外修正
        return f[n][0]  # f[n][0] 即全体元素中能取得的最大、且能被 3 整除的和
