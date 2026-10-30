# 题目：518. 零钱兑换 II（Coin Change II）
# 思路：完全背包求组合数。f[i][j] 表示用前 i 种硬币凑出金额 j 的方案数，金额从小到大枚举以允许同一种硬币重复使用。
# 时间复杂度：O(m·n)，m 为硬币种类数、n 为金额；空间复杂度：O(m·n)，即 DP 表大小。
class Solution:  # LeetCode 约定的题解类
    def change(self, amount: int, coins: List[int]) -> int:  # 返回凑出 amount 的硬币组合数（顺序不同视为同一种）
        m, n = len(coins), amount  # m 是硬币种类数，n 是目标金额
        f = [[0] * (n + 1) for _ in range(m + 1)]  # f[i][j]：用前 i 种硬币凑出金额 j 的方案数
        f[0][0] = 1  # 不选硬币凑出 0 元，只有一种空方案
        for i, x in enumerate(coins, 1):  # i 从 1 开始，表示逐步加入第 i 种硬币，x 是它的面值
            for j in range(n + 1):  # 金额从小到大枚举，允许同一种硬币重复使用
                f[i][j] = f[i - 1][j]  # 完全不用第 i 种硬币的方案数
                if j >= x:  # 金额不小于面值才可能再放一枚
                    f[i][j] += f[i][j - x]  # 用掉一枚后，剩余金额仍可用前 i 种硬币
        return f[m][n]  # 用全部硬币凑出 amount 的方案数
