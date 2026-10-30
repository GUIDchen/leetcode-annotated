# 题目：132. 分割回文串 II（Palindrome Partitioning II）
# 思路：区间 DP 预处理 g[i][j] 表示 s[i..j] 是否回文，再用 f[i] 记录前缀 s[0..i] 的最少切分数，枚举最后一段回文转移。
# 时间复杂度：O(n^2)，预处理与切分 DP 各两层循环；空间复杂度：O(n^2)，回文表。
class Solution:  # LeetCode 约定的题解类
    def minCut(self, s: str) -> int:  # 返回最少切分数
        n = len(s)  # n 是字符串长度
        g = [[True] * n for _ in range(n)]  # 回文判定表，先全部置 True（长度 0/1 的区间天然回文）
        for i in range(n - 1, -1, -1):  # i 从后往前，保证递推要用的 g[i+1][j-1] 已算好
            for j in range(i + 1, n):  # j 从 i+1 开始，短区间已在初值里
                g[i][j] = s[i] == s[j] and g[i + 1][j - 1]  # 首尾相同且去掉首尾仍回文，则 s[i..j] 回文
        f = list(range(n))  # f[i] 为前缀 s[0..i] 的最少切分数，初始按最坏情况 0,1,2,... 赋值
        for i in range(1, n):  # 从左往右递推每个前缀
            for j in range(i + 1):  # 枚举最后一段回文 s[j..i] 的起点 j
                if g[j][i]:  # 只有 s[j..i] 回文才可作为最后一段
                    f[i] = min(f[i], 1 + f[j - 1] if j else 0)  # j 为 0 表示整个前缀就是回文、无需切；否则在 f[j-1] 的基础上再切一刀
        return f[-1]  # 返回整个字符串的最少切分数
