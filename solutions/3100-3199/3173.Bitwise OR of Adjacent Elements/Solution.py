# 题目：3173. 相邻元素的按位或（Bitwise OR of Adjacent Elements）
# 思路：itertools.pairwise 把数组变成相邻元素对，再对每对求按位或，直接得到长度为 n-1 的答案。
# 时间复杂度：O(n)，遍历一次；空间复杂度：O(n)，答案列表（不计返回值则 O(1)）。
class Solution:  # LeetCode 约定的题解类
    def orArray(self, nums: List[int]) -> List[int]:  # nums 是输入数组，返回相邻元素按位或组成的新数组
        return [a | b for a, b in pairwise(nums)]  # pairwise(nums) 依次给出相邻的两个元素 (a, b)，列表推导把它们的按位或收集成结果
