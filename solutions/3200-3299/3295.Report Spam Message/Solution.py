# 题目：3295. 举报垃圾信息（Report Spam Message）
# 思路：把禁用词转成集合，统计消息中有多少个单词命中禁用词，数量达到 2 即为垃圾信息。
# 时间复杂度：O(n + m)，n 为消息单词数、m 为禁用词数；空间复杂度：O(m)，集合保存禁用词。
class Solution:  # LeetCode 约定的题解类
    def reportSpam(self, message: List[str], bannedWords: List[str]) -> bool:  # message 是整条消息的单词列表，bannedWords 是禁用词表
        s = set(bannedWords)  # 用集合把禁用词去重，单次查询是 O(1)
        return sum(w in s for w in message) >= 2  # 统计命中禁用词的单词个数，达到 2 个就判为垃圾信息
