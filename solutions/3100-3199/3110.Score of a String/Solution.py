# 题目：3110. 字符串的分数（Score of a String）
# 思路：把字符映射为 ASCII 码，用 pairwise 两两配对，累加每对相邻字符差值的绝对值。
# 时间复杂度：O(n)，遍历一次字符串；空间复杂度：O(1)，pairwise 惰性产出配对，不额外存数组。
class Solution:  # LeetCode 约定的题解类
    def scoreOfString(self, s: str) -> int:  # s 是输入字符串
        return sum(abs(a - b) for a, b in pairwise(map(ord, s)))  # 转成 ASCII 码后相邻两两作差、取绝对值并求和
