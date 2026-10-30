# 题目：561. 数组拆分（Array Partition）
# 思路：原地升序排序后，按下标 0、2、4… 取每组较小者求和；排序让相邻配对的最小值之和最大。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，排序在原数组上原地进行。
class Solution:  # LeetCode 约定的题解类
    def arrayPairSum(self, nums: List[int]) -> int:  # nums 是待配对的整数数组，返回每对较小值之和的最大值
        nums.sort()  # 原地升序排序，使相邻元素配对时较小值尽量大
        return sum(nums[::2])  # 切片 nums[::2] 取下标 0、2、4…（每组较小者），求和后返回
