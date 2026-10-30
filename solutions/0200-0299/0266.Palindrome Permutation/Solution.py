# 题目：266. 回文排列（Palindrome Permutation）
# 思路：用 Counter 统计字符频次，回文排列最多允许一个字符出现奇数次。
# 时间复杂度：O(n)；空间复杂度：O(1)，字符集大小有限。
class Solution:  # LeetCode 约定的题解类
    def canPermutePalindrome(self, s: str) -> bool:  # s 为待判定的字符串，返回它能否重排成回文
        return sum(v & 1 for v in Counter(s).values()) < 2  # v & 1 判断某字符是否出现奇数次，奇数次字符个数小于 2 即可
