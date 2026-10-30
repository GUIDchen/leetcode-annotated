# 题目：1682. 最长回文子序列 II（Longest Palindromic Subsequence II）
# 思路：区间记忆化搜索。dfs(i, j, x) 表示在 s[i..j] 中、外层已选字符 x 时能取到的最长「相邻字符不同」回文子序列长度；两端字符相同时才能同时取用，否则分别丢掉一端取较大值。
# 时间复杂度：O(n^2 · 26) 个状态，每个状态常数次转移；空间复杂度：O(n^2 · 26) 的记忆化开销。
class Solution:  # LeetCode 约定的题解类
    def longestPalindromeSubseq(self, s: str) -> int:  # 求满足「相邻字符两两不同」的最长回文子序列长度
        @cache  # cache 自动按参数缓存结果，相当于自顶向下的记忆化数组
        def dfs(i, j, x):  # 递归函数：区间 [i, j]，外层已经用掉的字符为 x（空串表示还没用字符）
            if i >= j:  # 区间长度不足 2，无法再构成一对回文，返回 0
                return 0  # 空区间返回 0
            if s[i] == s[j] and s[i] != x:  # 两端字符相同，且与外层字符不同，才能把它们同时纳入回文
                return dfs(i + 1, j - 1, s[i]) + 2  # 两端各取一个，长度加 2，并把该字符作为新的外层字符继续向里搜
            return max(dfs(i + 1, j, x), dfs(i, j - 1, x))  # 两端不可同时取用，分别丢掉左端与右端，取较优者

        ans = dfs(0, len(s) - 1, '')  # 从整个串开始搜，空串表示外层还没有字符
        dfs.cache_clear()  # 清空缓存，避免同一对象被多次调用时残留上一次的中间结果
        return ans  # 返回答案
