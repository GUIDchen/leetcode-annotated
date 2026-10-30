# 3627. Maximum Median Sum of Subsequences of Size 3（3627. 中位数之和的最大值）
# 核心思路：排序后把最小的 n/3 个数留作各三元组的最小值，剩余的 2n/3 个数两两成组，每组中位数取其中较大者，即从下标 n/3 起每隔 2 取一个累加。
# 复杂度：时间 O(n log n)（排序），空间 O(1)（不计排序内部开销）。
class Solution:  # 定义题解类
    def maximumMedianSum(self, nums: List[int]) -> int:  # 求所有三元组中位数之和的最大值
        nums.sort()  # 升序排序，便于贪心分组
        return sum(nums[len(nums) // 3 :: 2])  # 从 n/3 起每隔 2 取一个作为中位数并求和
