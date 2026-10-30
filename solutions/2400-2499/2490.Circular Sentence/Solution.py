# 题目：2490. 回环句（Circular Sentence）
# 思路：按空白切出单词，检查每个单词末字符是否等于下一个单词的首字符，最后一个接回第一个。
# 时间复杂度：O(n)，切分与检查各一遍；空间复杂度：O(n)，保存全部单词。
class Solution:  # LeetCode 约定的题解类
    def isCircularSentence(self, sentence: str) -> bool:  # sentence 是按空格分隔的单词串，判断首尾字符是否环环相扣
        ss = sentence.split()  # 按空白切分成单词列表
        n = len(ss)  # 单词个数，用于取模回环
        return all(s[-1] == ss[(i + 1) % n][0] for i, s in enumerate(ss))  # 每个单词末字符都等于下一个单词（最后一个接回第 0 个）的首字符时返回 True
