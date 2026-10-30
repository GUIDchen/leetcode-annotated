# 题目：2586. 统计范围内的元音字符串数（Count the Number of Vowel Strings in Range）
# 思路：切片取出 [left, right] 区间内的字符串，用生成器表达式逐个判断首尾字母是否都在 'aeiou' 中，再求和。
# 时间复杂度：O(right - left + 1)；空间复杂度：O(right - left + 1)，切片会复制一段子数组（生成器本身 O(1)）。
class Solution:  # LeetCode 约定的题解类
    def vowelStrings(self, words: List[str], left: int, right: int) -> int:  # words 为字符串数组，left/right 是闭区间端点
        return sum(  # 对区间内满足条件的字符串个数求和
            w[0] in 'aeiou' and w[-1] in 'aeiou' for w in words[left : right + 1]  # 首字母与尾字母都是元音才算真；切片右端要 +1 才是闭区间
        )  # sum 结束
