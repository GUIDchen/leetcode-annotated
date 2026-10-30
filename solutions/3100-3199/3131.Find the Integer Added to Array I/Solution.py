# 题目：3131. 找出与数组相加的整数 I（Find the Integer Added to Array I）
# 思路：nums2 是 nums1 每个元素加同一个整数 x 得到，最小值同步平移，故 x = min(nums2) - min(nums1)。
# 时间复杂度：O(n)，两次找最小值；空间复杂度：O(1)，不使用额外空间（min 是内置函数，无需 import）。
class Solution:  # LeetCode 约定的题解类
    def addedInteger(self, nums1: List[int], nums2: List[int]) -> int:  # nums1 是原数组，nums2 是整体加上 x 后的数组；List 由判题环境提供，注解不补 import
        return min(nums2) - min(nums1)  # 两组最小值相差 x，直接相减得到被加的整数
