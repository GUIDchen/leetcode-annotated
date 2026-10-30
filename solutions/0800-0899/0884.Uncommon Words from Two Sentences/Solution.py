# 题目：884. 两句话中的不常见单词（Uncommon Words from Two Sentences）
# 思路：把两个句子按空格拆词，用 Counter 相加统计每个单词的总出现次数，再筛出次数为 1 的单词。
# 时间复杂度：O(n + m)，两个句子各扫一遍；空间复杂度：O(n + m)，哈希表保存所有单词。
class Solution:  # LeetCode 约定的题解类
    def uncommonFromSentences(self, s1: str, s2: str) -> List[str]:  # s1、s2：两个用空格分隔单词的句子
        cnt = Counter(s1.split()) + Counter(s2.split())  # 两个句子的词频相加，得到每个单词在全局的出现次数
        return [s for s, v in cnt.items() if v == 1]  # 只保留全局只出现一次的单词
