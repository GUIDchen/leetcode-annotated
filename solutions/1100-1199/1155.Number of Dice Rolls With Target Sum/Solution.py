# 题目：1155. 掷骰子等于目标和的方法数（Number of Dice Rolls With Target Sum）
# 思路：动态规划，f[i][j] 表示 i 颗骰子掷出和为 j 的方案数，按最后一颗骰子的点数 1..k 转移。
# 时间复杂度：O(n·target·k)；空间复杂度：O(n·target)。
class Solution:  # LeetCode 约定的题解类
    def numRollsToTarget(self, n: int, k: int, target: int) -> int:  # n 颗骰子、每颗 1..k 面，返回和为 target 的方案数（取模）
        f = [[0] * (target + 1) for _ in range(n + 1)]  # f[i][j]：i 颗骰子掷出和为 j 的方案数，初始全 0
        f[0][0] = 1  # 边界：0 颗骰子只有和为 0 这一种空方案
        mod = 10**9 + 7  # 取模常数 1e9+7，防止方案数溢出
        for i in range(1, n + 1):  # 逐颗增加骰子
            for j in range(1, min(i * k, target) + 1):  # 枚举 i 颗骰子可达的和 j，上界受 i*k 与 target 限制
                for h in range(1, min(j, k) + 1):  # 枚举第 i 颗骰子的点数 h（1..k 且不超过 j）
                    f[i][j] = (f[i][j] + f[i - 1][j - h]) % mod  # 转移：累加前 i-1 颗和为 j-h 的方案数，再取模
        return f[n][target]  # 返回 n 颗骰子凑出 target 的方案数
