# 题目：521. 最长特殊序列 Ⅰ（Longest Uncommon Subsequence I）
# 思路：较长串本身一定不是较短串的子序列；只有两串完全相等时才没有特殊序列。
# 时间复杂度：O(n)，只做一次字符串比较；空间复杂度：O(1)，不使用额外空间。
class Solution:  # LeetCode 约定的题解类
    def findLUSlength(self, a: str, b: str) -> int:  # a、b：两个字符串；返回最长特殊序列的长度，不存在时返回 -1
        return -1 if a == b else max(len(a), len(b))  # 相等则无解返回 -1，否则返回两串长度的较大值（较长串整体即为答案）
