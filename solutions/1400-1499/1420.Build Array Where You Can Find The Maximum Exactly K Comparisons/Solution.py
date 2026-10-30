# 题目：1420. 生成数组（Build Array Where You Can Find The Maximum Exactly K Comparisons）
# 核心思路：dp[i][c][j] 表示长度 i、search_cost 为 c、末尾最大值恰为 j 的方案数；末位不超 j 时 c 不变，恰取 j 时 c 加一。
# 时间复杂度：O(n·k·m²)，状态 n·k·m 再乘一层枚举旧最大值；空间复杂度：O(n·k·m)。
class Solution:  # LeetCode 约定的题解类
    def numOfArrays(self, n: int, m: int, k: int) -> int:  # n：数组长度；m：取值上界；k：要求的 search_cost
        if k == 0:  # 长度至少为 1，首次更新必然发生，k 为 0 时无解
            return 0  # 返回 0 种方案
        dp = [[[0] * (m + 1) for _ in range(k + 1)] for _ in range(n + 1)]  # 三维 dp：长度、更新次数、末尾最大值
        mod = 10**9 + 7  # 取模用的常数
        for i in range(1, m + 1):  # 长度 1 的初始状态
            dp[1][1][i] = 1  # 长度 1 且最大值恰为 i 时只发生 1 次更新，各 1 种方案
        for i in range(2, n + 1):  # 逐层推进到长度 n
            for c in range(1, min(k + 1, i + 1)):  # 更新次数不超过长度 i，也不超过 k
                for j in range(1, m + 1):  # 枚举当前末尾最大值 j
                    dp[i][c][j] = dp[i - 1][c][j] * j  # 最大值保持 j：新元素可取 1..j 共 j 种（取模在内层累加时统一处理）
                    for j0 in range(1, j):  # 枚举更小的旧最大值 j0（j0 < j）
                        dp[i][c][j] += dp[i - 1][c - 1][j0]  # 新元素恰为 j 时触发一次更新，把所有 j0 的方案累加上来
                        dp[i][c][j] %= mod  # 边加边取模，避免数值过大
        ans = 0  # 汇总答案
        for i in range(1, m + 1):  # 遍历所有可能的末尾最大值
            ans += dp[n][k][i]  # 累加长度 n、恰 k 次更新的方案数
            ans %= mod  # 取模
        return ans  # 返回总方案数
