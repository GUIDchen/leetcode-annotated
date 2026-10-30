# 题目：2114. 句子中的最多单词数（Maximum Number of Words Found in Sentences）
# 思路：单个句子的单词数 = 空格数 + 1；对所有句子取空格数最大值后再加一。
# 时间复杂度：O(L)，L 为所有句子的总字符数；空间复杂度：O(1)，生成器不额外存储数据。
class Solution:# LeetCode 约定的题解类
    def mostWordsFound(self, sentences: List[str]) -> int:# sentences：所有句子；返回单词数的最大值
        return 1 + max(s.count(' ') for s in sentences)# 空格数加一即单词数，取所有句子中的最大值
