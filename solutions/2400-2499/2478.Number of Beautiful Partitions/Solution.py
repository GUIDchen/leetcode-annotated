# 题目：2478. 完美分割的方案数（Number of Beautiful Partitions）
# 思路：把字符串切成 k 段，每段长度至少 minLength 且以质数数字(2/3/5/7)开头、以非质数数字结尾；f[i][j] 表示前 i 个字符切成 j 段且第 j 段结束在 i 的方案数，g[i][j] 是同一 j 下 f 的前缀和，转移时用 g 一次取到所有合法前一段终点的方案总数。
# 时间复杂度：O(n·k)，i 与 j 两层循环；空间复杂度：O(n·k)，两个 (n+1)×(k+1) 的 DP 表。
class Solution:  # LeetCode 约定的题解类
    def beautifulPartitions(self, s: str, k: int, minLength: int) -> int:  # s：原字符串；k：段数；minLength：每段最小长度；返回方案数
        primes = '2357'  # 质数数字集合，用字符串的 in 判断即可
        if s[0] not in primes or s[-1] in primes:  # 首字符必须是质数数字、末字符必须不是质数数字，否则不可能切出任何一段
            return 0  # 直接返回 0 种方案
        mod = 10**9 + 7  # 取模常量，防止方案数溢出
        n = len(s)  # 字符串长度，后面下标都以它为上界
        f = [[0] * (k + 1) for _ in range(n + 1)]  # f[i][j]：前 i 个字符切成 j 段、且第 j 段结束在 i 的方案数
        g = [[0] * (k + 1) for _ in range(n + 1)]  # g[i][j]：f[0..i][j] 的前缀和，用于 O(1) 取到所有合法前一段终点的方案数之和
        f[0][0] = g[0][0] = 1  # 边界：空前缀切成 0 段有 1 种方案（空方案）
        for i, c in enumerate(s, 1):  # 从 1 开始枚举前缀长度 i，c 是第 i 个字符（1-based）
            if i >= minLength and c not in primes and (i == n or s[i] in primes):  # 位置 i 可作为段尾：长度够、当前字符非质数数字、且后面要么到末尾要么是质数数字（下一段开头）
                for j in range(1, k + 1):  # 枚举已经切出的段数 j
                    f[i][j] = g[i - minLength][j - 1]  # 转移：前一段结束位置 t 满足 t <= i-minLength，前缀和直接给出这些方案的累加值
            for j in range(k + 1):  # 把 f[i][j] 累进前缀和 g[i][j]
                g[i][j] = (g[i - 1][j] + f[i][j]) % mod  # 前缀和递推并取模
        return f[n][k]  # 返回整个字符串切成 k 段的方案数
