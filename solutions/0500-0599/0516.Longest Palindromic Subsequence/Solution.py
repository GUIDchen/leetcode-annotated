# 题目：516. 最长回文子序列（Longest Palindromic Subsequence）
# 思路：区间 DP。f[i][j] 表示子串 s[i..j] 的最长回文子序列长度；两端相等时由 f[i+1][j-1]+2 转移，否则取去掉某一端的较大值。
# 时间复杂度：O(n²)，每个区间算一次；空间复杂度：O(n²)，即 DP 表大小。
class Solution:  # LeetCode 约定的题解类
    def longestPalindromeSubseq(self, s: str) -> int:  # 返回字符串 s 的最长回文子序列长度
        n = len(s)  # 字符串长度
        f = [[0] * n for _ in range(n)]  # f[i][j]：子串 s[i..j] 的最长回文子序列长度
        for i in range(n):  # 先把长度为 1 的区间处理好
            f[i][i] = 1  # 单字符自身就是长度 1 的回文
        for i in range(n - 1, -1, -1):  # 左端点倒序，保证 f[i+1][...] 已经算出
            for j in range(i + 1, n):  # 右端点正序，保证 f[...][j-1] 已经算出
                if s[i] == s[j]:  # 两端相同，可以同时并入回文
                    f[i][j] = f[i + 1][j - 1] + 2  # 内部最优长度再加两端的 2 个字符
                else:  # 两端不同，必须至少舍去一端
                    f[i][j] = max(f[i + 1][j], f[i][j - 1])  # 两种舍弃方式取较大者
        return f[0][-1]  # 整个字符串区间的答案
