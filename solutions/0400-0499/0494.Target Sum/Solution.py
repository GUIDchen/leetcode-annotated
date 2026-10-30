# 题目：494. 目标和（Target Sum）
# 思路：给每个数加 + / - 号，等价于选出和为 (s - target) / 2 的「负号子集」，于是转成 0-1 背包计数：f[i][j] 表示前 i 个数凑出和 j 的方案数。
# 时间复杂度：O(n·s)，n 为元素个数、s 为总和；空间复杂度：O(n·s)，DP 二维表。
class Solution:  # LeetCode 约定的题解类
    def findTargetSumWays(self, nums: List[int], target: int) -> int:  # nums：非负整数数组；target：目标值；返回使正负号和为 target 的方案数
        s = sum(nums)  # s 为数组元素总和
        if s < target or (s - target) % 2:  # 全取负号都凑不到 target，或 s - target 为奇数（无法整除 2），都无解
            return 0  # 无解时方案数为 0
        m, n = len(nums), (s - target) // 2  # m：元素个数；n：需要凑出的「负号子集」目标和 (s - target) // 2
        f = [[0] * (n + 1) for _ in range(m + 1)]  # f[i][j]：前 i 个数中选出若干使和为 j 的方案数，初始全 0
        f[0][0] = 1  # 边界：不选任何数凑出和 0，视为 1 种方案
        for i, x in enumerate(nums, 1):  # enumerate 从 1 开始编号，方便用 f[i] 表示「前 i 个数」
            for j in range(n + 1):  # 枚举当前凑出的和 j
                f[i][j] = f[i - 1][j]  # 不选第 i 个数：方案数继承前 i - 1 个数的结果
                if j >= x:  # 只有 j ≥ x 时才可能把第 i 个数（值为 x）选进来
                    f[i][j] += f[i - 1][j - x]  # 选第 i 个数：累加前 i - 1 个数凑出 j - x 的方案数
        return f[m][n]  # 前 m 个数恰好凑出 n 的方案数即答案
