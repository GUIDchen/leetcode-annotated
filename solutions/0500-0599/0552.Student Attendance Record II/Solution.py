# 题目：552. 学生出勤记录 II（Student Attendance Record II）
# 思路：状态压缩 DP，f[j][k] 表示「已放了 j 个 A、末尾已有 k 个连续 L」时后续还能补出多少种合法记录；每轮往末尾补一位（P/A/L）合并三种转移，滚动 n 轮后 f[0][0] 即答案。
# 时间复杂度：O(n)，每轮只有 6 个状态、常数条转移；空间复杂度：O(1)，只用了两张 2×3 的表。
class Solution:  # LeetCode 约定的题解类
    def checkRecord(self, n: int) -> int:  # n 是记录长度，返回可奖励记录数（对 1e9+7 取模）
        mod = 10**9 + 7  # 取模常量
        f = [[1] * 3 for _ in range(2)]  # f[j][k]：已出现 j 个 A、末尾已有 k 个连续 L 时，后面还能补出多少种合法记录（空后缀算 1 种）
        for _ in range(n):  # 每轮往末尾再补一位字符，共补 n 位
            g = [[0] * 3 for _ in range(2)]  # 下一轮的状态表，全部先置 0
            for j in range(2):  # 枚举已出现的 A 的个数（不允许出现 2 个）
                for k in range(3):  # 枚举末尾连续 L 的个数（不允许连续 3 个）
                    ans = f[j][0]  # 下一位填 P：末尾连续 L 归零
                    if j == 0:  # 还没出现过 A，下一位才能填 A
                        ans += f[1][0]  # 填 A 后状态变成 (1, 0)
                    if k < 2:  # 连续 L 少于 2 个，下一位才能填 L
                        ans += f[j][k + 1]  # 填 L 后连续长度变成 k+1
                    g[j][k] = ans % mod  # 三种字符的贡献相加并取模，写入新状态表
            f = g  # 滚动更新当前状态
        return f[0][0]  # 0 个 A、末尾 0 个 L 的合法记录数就是答案
