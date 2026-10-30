# 题目：3701. 计算交替和（Compute Alternating Sum）
# 核心思路：利用 Python 切片步长，把偶数下标与奇数下标元素分别求和后相减，一步得到交替和。
# 复杂度：时间 O(n)，两次切片求和各扫一趟；空间 O(n)，切片会生成两个临时子数组。
class Solution:  # LeetCode 约定的题解类
    def alternatingSum(self, nums: List[int]) -> int:  # 返回数组的交替和：nums[0] - nums[1] + nums[2] - ...
        return sum(nums[0::2]) - sum(nums[1::2])  # 偶数下标之和减去奇数下标之和即交替和
