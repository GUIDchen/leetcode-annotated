# 题目：1855. 下标对中的最大距离（Maximum Distance Between a Pair of Values）
# 思路：两个数组都非递增，把 nums2 反转成非递减，对每个 i 用二分找出最后一个 >= nums1[i] 的位置，换算成原下标 j 后取最大 j - i。
# 时间复杂度：O(n log m + m)，n = len(nums1)、m = len(nums2)；空间复杂度：O(1)，除输入的切片副本外只用常数额外空间。
class Solution:  # LeetCode 约定的题解类
    def maxDistance(self, nums1: List[int], nums2: List[int]) -> int:  # nums1、nums2 均非递增，求满足 i <= j 且 nums1[i] <= nums2[j] 的最大 j - i
        ans = 0  # 答案初值：没有合法下标对时距离为 0
        nums2 = nums2[::-1]  # 反转成非递减，才能在它上面二分
        for i, v in enumerate(nums1):  # 枚举 nums1 的下标 i 与值 v
            j = len(nums2) - bisect_left(nums2, v) - 1  # bisect_left 找第一个 >= v 的位置，换算回原数组下标即最大的合法 j
            ans = max(ans, j - i)  # j - i 可能为负，max 保留更优的旧答案
        return ans  # 返回最大距离
