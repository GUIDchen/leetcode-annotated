# 题目：3146. 两个字符串的排列差（Permutation Difference between Two Strings）
# 思路：用字典记录 s 中每个字符的下标，再遍历 t，把 |该字符在 s 中的下标 - 它在 t 中的下标| 求和即得排列差。
# 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(1)，字母表固定 26 项。
class Solution:  # LeetCode 约定的题解类
    def findPermutationDifference(self, s: str, t: str) -> int:  # s、t：题目保证 t 是 s 的一个排列
        d = {c: i for i, c in enumerate(s)}  # d：字符 → 它在 s 中的下标
        return sum(abs(d[c] - i) for i, c in enumerate(t))  # 遍历 t，累加每个字符在两串中位置差的绝对值
