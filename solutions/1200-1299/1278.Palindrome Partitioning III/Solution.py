# 题目：1278. 分割回文串 III（Palindrome Partitioning III）
# 思路：先用区间 DP 预处理 g[i][j]（把 s[i..j] 变成回文串的最少改动字符数），再用划分 DP 求切成 k 段的最小总代价。
# 时间复杂度：O(n^3 + n^2·k)，区间预处理 O(n^2) 之外还要枚举切点；空间复杂度：O(n^2 + n·k)。
class Solution:  # LeetCode 约定的题解类
    def palindromePartition(self, s: str, k: int) -> int:  # s 为原串，k 为要切成的段数，返回最少修改字符数
        n = len(s)  # 字符串长度
        g = [[0] * n for _ in range(n)]  # g[i][j]：把子串 s[i..j] 变成回文串所需的最少字符修改数
        for i in range(n - 1, -1, -1):  # 左端点从右往左，保证依赖的更短区间已经算好
            for j in range(i + 1, n):  # 右端点至少比左端点大 1；单字符区间在初始化时已为 0
                g[i][j] = int(s[i] != s[j])  # 两端字符不同则至少需要改 1 个字符
                if i + 1 < j:  # 剥掉两端后中间还有内容，需要把内层代价累加上去
                    g[i][j] += g[i + 1][j - 1]  # 内层区间的最少修改数

        f = [[0] * (k + 1) for _ in range(n + 1)]  # f[i][j]：把前 i 个字符切成 j 段的最小修改数
        for i in range(1, n + 1):  # 枚举前缀长度 i
            for j in range(1, min(i, k) + 1):  # 段数 j 不能超过前缀长度，也不能超过总段数 k
                if j == 1:  # 只切一段：整段前缀就是最后一段
                    f[i][j] = g[0][i - 1]  # 代价等于把 s[0..i-1] 变成回文串的代价
                else:  # 切多段：枚举最后一段的起点 h
                    f[i][j] = inf  # 用正无穷初始化最优值
                    for h in range(j - 1, i):  # h 是最后一段的起点，前面至少要留出 j-1 个字符
                        f[i][j] = min(f[i][j], f[h][j - 1] + g[h][i - 1])  # 前 h 个字符切 j-1 段，再加上最后一段的代价
        return f[n][k]  # 前 n 个字符切成 k 段的最小修改次数即为答案
