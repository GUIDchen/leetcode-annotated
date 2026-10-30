# 题目：416. 分割等和子集（Partition Equal Subset Sum）
# 思路：总和为奇数时必然无解；否则转成 0/1 背包，f[i][j] 表示前 i 个数能否恰好凑出和 j，目标是 f[n][总和/2]。
# 时间复杂度：O(n * sum)，两层循环；空间复杂度：O(n * sum)，二维布尔表。
class Solution:  # LeetCode 约定的题解类
    def canPartition(self, nums: List[int]) -> bool:  # nums 是正整数数组，判断能否分成两个元素和相等的子集
        m, mod = divmod(sum(nums), 2)  # divmod 同时得到目标值的一半 m 和余数 mod
        if mod:  # 余数不为 0，说明总和是奇数，无法均分
            return False  # 直接返回 False
        n = len(nums)  # n 是元素个数
        f = [[False] * (m + 1) for _ in range(n + 1)]  # f[i][j] 表示前 i 个数能否凑出和 j，初始全为 False
        f[0][0] = True  # 边界：前 0 个数凑出和 0 可行（什么都不选）
        for i, x in enumerate(nums, 1):  # enumerate 从 1 开始编号，i 表示「前 i 个数」
            for j in range(m + 1):  # 枚举所有可能的和 j
                f[i][j] = f[i - 1][j] or (j >= x and f[i - 1][j - x])  # 不选当前数，或选当前数（前提是 j >= x），两种选择取或
        return f[n][m]  # 返回前 n 个数能否凑出总和的一半
