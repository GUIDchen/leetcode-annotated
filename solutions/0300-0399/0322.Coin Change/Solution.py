# 题目：322. 零钱兑换（Coin Change）
# 思路：完全背包动态规划，f[i][j] 表示用前 i 种硬币凑出金额 j 的最少硬币数，转移时比较「不用」与「再用一枚」。
# 时间复杂度：O(m * n)，m 为硬币种数、n 为金额；空间复杂度：O(m * n)，使用二维 DP 表。
class Solution:  # LeetCode 约定的题解类
    def coinChange(self, coins: List[int], amount: int) -> int:  # coins 是硬币面值列表，amount 是目标金额，返回最少硬币数，凑不出返回 -1
        m, n = len(coins), amount  # m 为硬币种数，n 为目标金额
        f = [[inf] * (n + 1) for _ in range(m + 1)]  # 完全背包 DP 表，f[i][j] 表示用前 i 种硬币凑出金额 j 的最少硬币数，先全部置为无穷大
        f[0][0] = 0  # 边界：用 0 种硬币凑出金额 0 需要 0 枚
        for i, x in enumerate(coins, 1):  # 逐个考虑每种硬币，i 从 1 开始，对应 coins[i-1]
            for j in range(n + 1):  # 枚举目标金额 j，正序遍历以允许同种硬币重复使用
                f[i][j] = f[i - 1][j]  # 不用第 i 种硬币：直接继承前 i-1 种的结果
                if j >= x:  # 金额够用当前面值时才可能再放一枚
                    f[i][j] = min(f[i][j], f[i][j - x] + 1)  # 「再用一枚当前硬币」仍是 f[i][j-x]（同种可无限次），取两者较小值
        return -1 if f[m][n] >= inf else f[m][n]  # 仍是无穷大说明凑不出（其值远大于任何可行枚数），返回 -1
