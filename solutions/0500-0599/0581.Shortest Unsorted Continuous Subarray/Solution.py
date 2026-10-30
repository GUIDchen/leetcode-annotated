# 题目：581. 最短无序连续子数组（Shortest Unsorted Continuous Subarray）
# 核心思路：排序一份副本；左右两端与原数组相同的位置无需改动，中间夹住的区间即为最短需排序子数组。
# 时间复杂度：O(n log n)，排序是瓶颈；空间复杂度：O(n)，需要一份等长副本。
class Solution:  # LeetCode 约定的题解类
    def findUnsortedSubarray(self, nums: List[int]) -> int:  # nums 是输入整数数组
        arr = sorted(nums)  # 生成升序副本，作为目标形态（sorted 不修改原数组）
        l, r = 0, len(nums) - 1  # 双指针：l 从左端、r 从右端相向扫描
        while l <= r and nums[l] == arr[l]:  # 左端已经与排好序的结果一致
            l += 1  # 左指针右移，跳过有序前缀
        while l <= r and nums[r] == arr[r]:  # 右端已经与排好序的结果一致
            r -= 1  # 右指针左移，跳过有序后缀
        return r - l + 1  # 闭区间 [l, r] 的长度；若整体有序则 l > r，长度自然为 0
