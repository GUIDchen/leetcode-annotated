# 题目：1832. 判断句子是否为全字母句（Check if the Sentence Is Pangram）
# 思路：对字符串去重，若不同字符恰好 26 种，就说明 26 个小写字母全部出现。
# 时间复杂度：O(n)，n 为句子长度；空间复杂度：O(1)，集合最多 26 个元素。
class Solution:  # LeetCode 约定的题解类
    def checkIfPangram(self, sentence: str) -> bool:  # sentence：只含小写字母的句子；返回它是否为全字母句
        return len(set(sentence)) == 26  # 去重后字符种类正好 26 种，说明包含全部小写字母
