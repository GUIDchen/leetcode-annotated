# 题目：28. 找出字符串中第一个匹配项的下标（Find the Index of the First Occurrence in a String）
# 思路：朴素枚举所有可能的起点 i，用切片取出长度 m 的子串与 needle 比较；i 从小到大枚举，第一个相等的起点就是答案。
# 时间复杂度：O((n-m+1)·m)，最坏情况每次比较都扫完整个 needle；空间复杂度：O(m)，切片会生成临时子串（不计入则 O(1)）。
class Solution:  # LeetCode 约定的题解类
    def strStr(self, haystack: str, needle: str) -> int:  # haystack：主串；needle：模式串；返回首次出现的下标，找不到返回 -1
        n, m = len(haystack), len(needle)  # n、m 分别是主串和模式串的长度
        for i in range(n - m + 1):  # 起点 i 只取 0..n-m，保证从 i 开始长度 m 的子串不越界
            if haystack[i : i + m] == needle:  # 用切片取出长度 m 的子串，与模式串比较内容
                return i  # 相等说明找到第一个匹配项，返回起点下标
        return -1  # 所有起点都不匹配，按题目要求返回 -1
