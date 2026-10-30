# 题目：2787. 将一个数字表示成幂的和的方案数（Ways to Express an Integer as Sum of Powers）
# 核心思路：0-1 背包计数 DP。底数 i 的 x 次幂是物品 i 的体积，每个底数最多用一次；f[i][j] 表示用 1..i 凑出 j 的方案数。
# 时间复杂度：O(n^2)，n 个底数各扫一遍目标和；空间复杂度：O(n^2)，二维 DP 表。
class Solution:  # LeetCode 约定的题解类
    def numberOfWays(self, n: int, x: int) -> int:  # n：目标和；x：幂次；返回把 n 写成若干互不相同正整数 x 次幂之和的方案数
        mod = 10**9 + 7  # 答案对 1e9+7 取模
        f = [[0] * (n + 1) for _ in range(n + 1)]  # (n+1) x (n+1) 的 DP 表，初始全 0
        f[0][0] = 1  # 边界：一个数都不用凑出 0，方案数为 1
        for i in range(1, n + 1):  # 逐个考虑底数 i（每个最多选一次）
            k = pow(i, x)  # i 的 x 次幂，即选 i 时贡献的体积
            for j in range(n + 1):  # 枚举目标和 j
                f[i][j] = f[i - 1][j]  # 不选 i：方案数从上一行继承
                if k <= j:  # 只有幂值 k ≤ j 才装得进容量 j
                    f[i][j] = (f[i][j] + f[i - 1][j - k]) % mod  # 选 i：累加凑出 j-k 的方案数，并按模数取余
        return f[n][n]  # 返回用 1..n 凑出和 n 的方案数
