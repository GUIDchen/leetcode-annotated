# 题目：2828. 判别首字母缩略词（Check if a String Is an Acronym of Words）
# 思路：按顺序把每个单词的首字母拼成一个新串，再与 s 比较是否完全相等。
# 时间复杂度：O(n)，n 为所有单词长度之和；空间复杂度：O(m)，m 为单词个数，用于存放拼接出的缩略词。
class Solution:  # LeetCode 约定的题解类
    def isAcronym(self, words: List[str], s: str) -> bool:  # words：单词列表；s：待判断的缩略词；返回 s 是否为这些单词首字母的拼接
        return "".join(w[0] for w in words) == s  # 用生成器按顺序取每个单词的首字母拼成字符串，再判断是否与 s 相等
