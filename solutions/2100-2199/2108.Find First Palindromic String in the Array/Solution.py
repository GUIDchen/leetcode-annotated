# 题目：2108. 找出数组中的第一个回文字符串（Find First Palindromic String in the Array）
# 思路：用生成器表达式按顺序筛选回文串，w[::-1] 是字符串反转，next 取第一个，没有则返回空串。
# 时间复杂度：O(L)，L 为所有字符串字符总数；空间复杂度：O(1) 额外空间（切片反转是逐串临时开销）。
class Solution:  # LeetCode 约定的题解类
    def firstPalindrome(self, words: List[str]) -> str:  # words 是字符串数组，返回其中第一个回文串
        return next((w for w in words if w == w[::-1]), "")  # 生成器按原顺序惰性产出满足 w == w[::-1] 的字符串，next 取第一个，缺省值为空串
