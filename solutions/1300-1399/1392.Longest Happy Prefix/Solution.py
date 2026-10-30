# 题目：1392. 最长快乐前缀（Longest Happy Prefix）
# 思路：从最短的后缀长度开始枚举起点 i，直接切片比较前缀 s[:-i] 与后缀 s[i:]；第一个相等的前后缀就是最长的（i 越小长度越长）。
# 时间复杂度：O(n^2)，每次切片比较要 O(n)；空间复杂度：O(n)，切片会生成新的字符串。
class Solution:  # LeetCode 约定的题解类
    def longestPrefix(self, s: str) -> str:  # s 是待求解的字符串
        for i in range(1, len(s)):  # i 是后缀的起始下标，从 1 开始，保证前缀长度 len(s) - i 小于 n（真前缀）
            if s[:-i] == s[i:]:  # 前缀 s[:-i] 与后缀 s[i:] 长度相同，直接比较内容
                return s[i:]  # 找到最长的快乐前缀，题目要求返回这段前缀本身
        return ''  # 没有任何非空真前缀同时是后缀，返回空串
