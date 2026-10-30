# 题目：1816. 截断句子（Truncate Sentence）
# 思路：按空格切分出所有单词，取前 k 个再用单个空格重新拼接，单词顺序与原句一致。
# 时间复杂度：O(n)，切分与拼接各扫描一遍字符串；空间复杂度：O(n)，保存切分出的单词及结果字符串。
class Solution:  # LeetCode 约定的题解类
    def truncateSentence(self, s: str, k: int) -> str:  # s：原句子；k：要保留的单词个数
        return ' '.join(s.split()[:k])  # split() 按任意空白切分，切片取前 k 个单词，再用空格拼回句子
