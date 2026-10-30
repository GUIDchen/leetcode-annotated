# 3689. 最大子数组总值 I / Maximum Total Subarray Value I
# 核心思路：子数组的值等于最大值减最小值，取 k 份时的最大总和就是 k 乘以全局极差
# 时间复杂度 O(n)，空间复杂度 O(1)
class Solution:  # 题解类
    def maxTotalValue(self, nums: List[int], k: int) -> int:  # 返回 k 个子数组值的最大总和
        return k * (max(nums) - min(nums))  # 每个子数组都能取到全局极差，乘 k 即可
