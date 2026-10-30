# 题目：459. 重复的子字符串（Repeated Substring Pattern）
# 思路：在 s+s 中从下标 1 开始查找 s；若索引小于 len(s)，说明存在更早的循环匹配，即 s 由某个子串重复构成。
# 时间复杂度：O(n^2)（index 最坏为朴素匹配）；空间复杂度：O(n)（s+s 生成的临时字符串）。
class Solution:  # LeetCode 约定的题解类
    def repeatedSubstringPattern(self, s: str) -> bool:  # s 是待判断的字符串，判断它能否由某个子串重复多次构成
        return (s + s).index(s, 1) < len(s)  # 从下标 1 开始在 s+s 中查找 s，索引小于 len(s) 说明存在更早的循环匹配
