# 题目：1935. 可以输入的最大单词数（Maximum Number of Words You Can Type）
# 思路：用集合记录坏字母，把 text 按空白切分成单词，逐词检查是否所有字母都可用。
# 时间复杂度：O(|text| + |brokenLetters|)；空间复杂度：O(1)，集合最多 26 个元素。
class Solution:  # LeetCode 约定的题解类
    def canBeTypedWords(self, text: str, brokenLetters: str) -> int:  # 返回能够完整敲出的单词数
        s = set(brokenLetters)  # 把损坏的字母放进集合，方便 O(1) 查询
        return sum(all(c not in s for c in w) for w in text.split())  # 拆分单词后逐词判断：该词所有字母都不在坏字母集合中才计入
