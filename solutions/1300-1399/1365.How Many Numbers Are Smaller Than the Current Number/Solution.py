# 题目：1365. 有多少小于当前数字的数字（How Many Numbers Are Smaller Than the Current Number）
# 思路：复制并排序，对每个元素用 bisect_left 求它在有序数组中的首个位置，该下标正好等于比它小的元素个数。
# 时间复杂度：O(n log n)，排序加 n 次二分；空间复杂度：O(n)，副本数组 arr。
class Solution:  # LeetCode 约定的题解类
    def smallerNumbersThanCurrent(self, nums: List[int]) -> List[int]:  # nums 是待统计的数组，返回每个元素对应的更小元素个数
        arr = sorted(nums)  # 复制并排序，得到有序数组
        return [bisect_left(arr, x) for x in nums]  # 对每个 x 用 bisect_left 求首个不小于它的位置，该下标就是比它小的元素个数
