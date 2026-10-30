# 题目：2540. 最小公共值（Minimum Common Value）
# 思路：利用两个数组都升序，用双指针同步推进，较小一侧右移，首次相等即最小公共值。
# 时间复杂度：O(m + n)；空间复杂度：O(1)，只用两个下标。
class Solution:  # LeetCode 约定的题解类
    def getCommon(self, nums1: List[int], nums2: List[int]) -> int:  # nums1、nums2 均为升序，返回最小公共值
        i = j = 0  # 链式赋值：i、j 两个指针同时从 0 开始
        m, n = len(nums1), len(nums2)  # m、n 分别是两个数组的长度
        while i < m and j < n:  # 任一数组越界就结束查找
            if nums1[i] == nums2[j]:  # 两值相等，即最小公共值
                return nums1[i]  # 直接返回
            if nums1[i] < nums2[j]:  # nums1[i] 偏小
                i += 1  # 右移 i 去追
            else:  # 否则 nums2[j] 偏小
                j += 1  # 右移 j 去追
        return -1  # 两数组没有公共值，返回 -1
