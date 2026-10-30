# 题目：1408. 数组中的字符串匹配（String Matching in an Array）
# 思路：对每个单词用 any 扫描其它单词，判断它是否是对方的子串（跳过自身）；命中即加入答案，保证不重复。
# 时间复杂度：O(n^2 * L)，n 为单词数、L 为串长；空间复杂度：O(1)，不计返回结果。
class Solution:  # LeetCode 约定的题解类
    def stringMatching(self, words: List[str]) -> List[str]:  # words 为待检查的字符串列表
        ans = []  # 收集所有是其它单词子串的字符串
        for i, s in enumerate(words):  # 同时取得下标 i 与单词 s
            if any(i != j and s in t for j, t in enumerate(words)):  # 跳过自身，且 s 是某个 t 的子串
                ans.append(s)  # 满足条件就记录，循环天然去重
        return ans  # 返回所有匹配的字符串
