# 题目：2559. 统计范围内的元音字符串数（Count Vowel Strings in Ranges）
# 核心思路：先筛出「首尾都是元音」的单词下标（天然升序），再用二分左右端点之差回答每个查询区间。
# 时间复杂度：O(n + q log n)，n 为单词数、q 为查询数；空间复杂度：O(n)，保存有序下标。
class Solution:  # LeetCode 约定的题解类
    def vowelStrings(self, words: List[str], queries: List[List[int]]) -> List[int]:  # words：单词表；queries：若干闭区间 [l, r]
        vowels = set("aeiou")  # 元音集合，成员判断是 O(1)
        nums = [i for i, w in enumerate(words) if w[0] in vowels and w[-1] in vowels]  # 首尾字母都是元音的下标，列表推导保证升序
        return [bisect_right(nums, r) - bisect_left(nums, l) for l, r in queries]  # 每个区间内元素个数 = 第一个大于 r 的位置 - 第一个大于等于 l 的位置
