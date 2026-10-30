# 题目：115. 不同的子序列（Distinct Subsequences）
# 思路：二维 DP，f[i][j] 表示 s 的前 i 个字符中选出 t 的前 j 个字符的方案数；字符不相等时继承上一行，相等时再加上左上角。
# 时间复杂度：O(m * n)，整张 DP 表遍历一次；空间复杂度：O(m * n)，需要 (m+1) x (n+1) 的表。
class Solution:  # LeetCode 约定的题解类
    def numDistinct(self, s: str, t: str) -> int:  # s 为原串，t 为目标串，返回不同子序列的个数
        m, n = len(s), len(t)  # 记录两个串的长度
        f = [[0] * (n + 1) for _ in range(m + 1)]  # 二维 DP 表，多开一行一列用来表示空前缀
        for i in range(m + 1):  # 边界：t 是空串时方案数恒为 1
            f[i][0] = 1  # 把第一列全部置 1
        for i, a in enumerate(s, 1):  # 从 1 开始枚举行号 i，同时取出 s 的第 i 个字符 a（enumerate 的 start=1）
            for j, b in enumerate(t, 1):  # 从 1 开始枚举列号 j，同时取出 t 的第 j 个字符 b
                f[i][j] = f[i - 1][j]  # 不选 a 这一位，方案数继承上一行
                if a == b:  # 字符相同，a 才有资格去匹配 b
                    f[i][j] += f[i - 1][j - 1]  # 累加去掉这两个字符后的子问题方案数
        return f[m][n]  # 整个 s 拼出整个 t 的方案总数
