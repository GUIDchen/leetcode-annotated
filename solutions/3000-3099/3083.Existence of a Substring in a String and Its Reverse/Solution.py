# 题目：3083. 字符串及其反转中是否存在同一子字符串（Existence of a Substring in a String and Its Reverse）
# 思路：用集合登记反转串中全部相邻字符对，再检查 s 的相邻字符对是否落在该集合里。
# 时间复杂度：O(n)；空间复杂度：O(n)，集合最多存 n-1 个二元组。
class Solution:  # LeetCode 约定的题解类
    def isSubstringPresent(self, s: str) -> bool:  # 判断 s 中是否存在长度 2 的子串，它同时出现在 s 和 s 的反转串中
        st = {(a, b) for a, b in pairwise(s[::-1])}  # pairwise 遍历相邻字符对：集合 st 收集反转串里出现的全部长度 2 子串
        return any((a, b) in st for a, b in pairwise(s))  # 只要 s 中有一对相邻字符也出现在 st 中，就返回 True
