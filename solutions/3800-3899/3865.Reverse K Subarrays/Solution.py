# 3865. 反转 K 个子数组 / Reverse K Subarrays
# 核心思路：每段长度 m = n // k，以 m 为步长枚举 k 段的起点，用切片 [::-1] 反转该段后原址写回。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(m)（每段切片产生的临时列表）。
class Solution:  # LeetCode 题解类
    def reverseSubarrays(self, nums: list[int], k: int) -> list[int]:  # 把 nums 均分为 k 段并逐段反转
        n = len(nums)  # 数组长度 n
        m = n // k  # 每段的长度（题目保证 n 能被 k 整除）
        for i in range(0, n, m):  # 以 m 为步长遍历每一段的起点
            nums[i : i + m] = nums[i : i + m][::-1]  # 取出该段、反转后原址写回
        return nums  # 返回反转后的数组
