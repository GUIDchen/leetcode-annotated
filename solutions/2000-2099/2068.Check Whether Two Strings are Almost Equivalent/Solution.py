# 题目：2068. 检查两个字符串是否几乎相等（Check Whether Two Strings are Almost Equivalent）
# 思路：先用 Counter 统计 word1 的字母频次，再把 word2 的字母频次减掉，最后判断每个字母的差值绝对值是否都不超过 3。
# 时间复杂度：O(n)，n 为字符串长度；空间复杂度：O(26) = O(1)，计数容器最多 26 个键。
class Solution:  # LeetCode 约定的题解类
    def checkAlmostEquivalent(self, word1: str, word2: str) -> bool:  # word1、word2 是两个待比较的字符串
        cnt = Counter(word1)  # 先统计 word1 中每个字母出现的次数
        for c in word2:  # 遍历 word2，把它的字母频次从计数中减掉
            cnt[c] -= 1  # 每出现一次就减 1，最终得到两串的频次差
        return all(abs(x) <= 3 for x in cnt.values())  # 所有字母频次差的绝对值都不超过 3 时才返回 True
