# 题目：1768. 交替合并字符串（Merge Strings Alternately）
# 思路：用 zip_longest 把两个字符串按位置配对，较短的串用空串补齐，再把每一对字符拼起来并用 join 连接成一个串。
# 时间复杂度：O(m + n)，每个字符只处理一次；空间复杂度：O(m + n)，生成器与结果串。
class Solution:  # LeetCode 约定的题解类
    def mergeAlternately(self, word1: str, word2: str) -> str:  # word1、word2 是待交替合并的两个字符串
        return ''.join(a + b for a, b in zip_longest(word1, word2, fillvalue=''))  # zip_longest 按位置配对（fillvalue 用空串补齐较短的一方），a + b 实现交替拼接，join 汇总成结果串
