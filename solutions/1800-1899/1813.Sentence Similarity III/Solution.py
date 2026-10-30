# 题目：1813. 句子相似性 III（Sentence Similarity III）
# 思路：把两句话拆成单词，长句记为 words1、短句记为 words2；分别统计相同的前缀与后缀长度，两者之和覆盖短句全部单词即相似。
# 时间复杂度：O(m + n)，m、n 为两句的单词数；空间复杂度：O(m + n)，用于存放切分后的单词。
class Solution:  # LeetCode 约定的题解类
    def areSentencesSimilar(self, sentence1: str, sentence2: str) -> bool:  # 判断两句话是否相似：短句能否由长句插入一整段句子得到
        words1, words2 = sentence1.split(), sentence2.split()  # 按空白切分，得到两句话的单词列表
        m, n = len(words1), len(words2)  # 两句各自的单词数
        if m < n:  # 确保 words1 是较长的那句
            words1, words2 = words2, words1  # 交换两个单词列表
            m, n = n, m  # 长度也要跟着一起交换
        i = j = 0  # i 统计公共前缀长度，j 统计公共后缀长度
        while i < n and words1[i] == words2[i]:  # 从前往后比对公共前缀
            i += 1  # 前缀长度加一
        while j < n and words1[m - 1 - j] == words2[n - 1 - j]:  # 从后往前比对公共后缀
            j += 1  # 后缀长度加一
        return i + j >= n  # 前后缀覆盖短句全部单词即相似（中间允许插入任意句子）
