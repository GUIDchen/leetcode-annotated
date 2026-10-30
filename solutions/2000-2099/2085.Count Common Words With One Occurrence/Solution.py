# 题目：2085. 统计出现过一次的公共字符串（Count Common Words With One Occurrence）
# 思路：用两个计数器分别统计两个数组的词频，再筛出在两个计数器里都恰好出现一次的单词并计数。
# 时间复杂度：O(m + n)，两次线性统计加一次遍历；空间复杂度：O(m + n)，两个计数器存放不同单词。
class Solution:  # LeetCode 约定的题解类
    def countWords(self, words1: List[str], words2: List[str]) -> int:  # words1、words2 为两个字符串数组，返回其中都只出现一次的词数
        cnt1 = Counter(words1)  # Counter 一次统计出 words1 每个单词的出现次数
        cnt2 = Counter(words2)  # Counter 一次统计出 words2 每个单词的出现次数
        return sum(v == 1 and cnt2[w] == 1 for w, v in cnt1.items())  # 生成器求和：v==1 且 words2 中也恰好一次时计 1，否则计 0
