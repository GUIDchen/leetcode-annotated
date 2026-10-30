# 4030. 判断 ASCII 值回文 / Check ASCII Palindromic
# 核心思路：把每个字符展开成 8 位二进制串并依次拼接，再判断拼接后的串是否为回文串。
# 复杂度：时间 O(8n)，空间 O(8n)（n 为字符串长度）。
class Solution:  # 题解类定义
    def isPalindromic(self, s: str) -> bool:  # 判断 s 中所有字符的 8 位二进制串拼接后是否为回文串
        t = ''.join(format(ord(c), '08b') for c in s)  # 用 format(c, '08b') 取每个字符的 8 位二进制表示并拼接
        return t == t[::-1]  # 与原串的反转串比较是否相等
