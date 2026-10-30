# 题目：2215. 找出两数组的不同（Find the Difference of Two Arrays）
# 思路：两个数组分别转成集合去重，集合差集 s1 - s2 与 s2 - s1 就是答案，最后各自转回列表。
# 时间复杂度：O(m + n)，建集合各扫一遍；空间复杂度：O(m + n)，存放两个集合与结果列表。
class Solution:  # LeetCode 约定的题解类
    def findDifference(self, nums1: List[int], nums2: List[int]) -> List[List[int]]:  # nums1、nums2 是两个输入数组
        s1, s2 = set(nums1), set(nums2)  # 分别去重；集合支持 O(1) 的成员判断和差集运算
        return [list(s1 - s2), list(s2 - s1)]  # s1 - s2 是只在 nums1 出现的值，s2 - s1 是只在 nums2 出现的值
