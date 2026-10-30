# 题目：1874. 两个数组的最小乘积和（Minimize Product Sum of Two Arrays）
# 思路：排序不等式——一个数组升序、另一个数组降序后逐位相乘再求和，即得到最小乘积和。
# 时间复杂度：O(n log n)，瓶颈是两次排序；空间复杂度：O(log n)，排序内部递归栈的额外开销。
class Solution:  # LeetCode 约定的题解类
    def minProductSum(self, nums1: List[int], nums2: List[int]) -> int:  # nums1、nums2：两个等长数组
        nums1.sort()  # 第一个数组升序排列
        nums2.sort(reverse=True)  # 第二个数组降序排列
        return sum(x * y for x, y in zip(nums1, nums2))  # 大值配小值，逐位乘积求和即最小乘积和
