# 题目：1143. 最长公共子序列（Longest Common Subsequence）
# 思路：二维 DP：f[i][j] 为两串前缀的 LCS 长度，末位相同则左上角加 1，否则取上、左较大值。
# 时间复杂度：O(m*n)；空间复杂度：O(m*n)。
class Solution:  # LeetCode 约定的题解类
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:  # 两个输入字符串，返回最长公共子序列长度
        m, n = len(text1), len(text2)  # 两个字符串的长度
        f = [[0] * (n + 1) for _ in range(m + 1)]  # 二维 DP 表，多一行一列表示空前缀，初值全 0
        for i in range(1, m + 1):  # 枚举 text1 的前缀长度
            for j in range(1, n + 1):  # 枚举 text2 的前缀长度
                if text1[i - 1] == text2[j - 1]:  # 两个前缀的末位字符相同（下标减 1）
                    f[i][j] = f[i - 1][j - 1] + 1  # 该字符必在公共子序列中，取左上角的值加 1
                else:  # 末位不同
                    f[i][j] = max(f[i - 1][j], f[i][j - 1])  # 丢掉其中一个末位字符，取两种选择的较大值
        return f[m][n]  # 完整两串的 LCS 长度
