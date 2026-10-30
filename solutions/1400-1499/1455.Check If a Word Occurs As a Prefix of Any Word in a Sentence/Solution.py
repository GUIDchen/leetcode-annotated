# 题目：1455. 检查单词是否为句中其他单词的前缀（Check If a Word Occurs As a Prefix of Any Word in a Sentence）
# 思路：用 split() 按空白切分句子，再用 startswith 逐词判断前缀，返回第一个匹配单词的 1 基下标。
# 时间复杂度：O(L)，L 为句子总长度；空间复杂度：O(L)，存放切分出的单词列表。
class Solution:  # LeetCode 约定的题解类
    def isPrefixOfWord(self, sentence: str, searchWord: str) -> int:  # sentence：句子；searchWord：待检查的前缀词；返回首个匹配的 1 基下标或 -1
        for i, s in enumerate(sentence.split(), 1):  # split() 按空白切分，enumerate 的第二个参数 1 让编号从 1 开始
            if s.startswith(searchWord):  # startswith 判断该单词是否以 searchWord 开头，即 searchWord 是它的前缀
                return i  # 首个匹配即返回，保证返回的是最小下标
        return -1  # 全部单词都不匹配，返回 -1
