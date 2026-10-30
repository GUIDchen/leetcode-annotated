# 题目：1356. 根据数字二进制下 1 的数目排序（Sort Integers by The Number of 1 Bits）
# 思路：用 sorted 搭配元组键 (1 的个数, 数值)，Python 会先比第一关键字、相同再比第二关键字。
# 时间复杂度：O(n log n)，排序为主；空间复杂度：O(n)，sorted 会产生新列表。
class Solution:  # LeetCode 约定的题解类
    def sortByBits(self, arr: List[int]) -> List[int]:  # 按 1 的个数升序，个数相同按数值升序
        return sorted(arr, key=lambda x: (x.bit_count(), x))  # 元组键：第一关键字是 bit_count()（1 的个数），第二关键字是数值本身
