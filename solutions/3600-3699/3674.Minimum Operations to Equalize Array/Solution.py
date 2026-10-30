# 3674. Minimum Operations to Equalize Array（数组元素相等的最小操作次数）
# 核心思路：只要存在与首元素不同的元素就返回 1，否则返回 0。
# 复杂度：时间 O(n)，空间 O(1)。
class Solution:  # 定义 Solution 类
    def minOperations(self, nums: List[int]) -> int:  # 求使数组元素全部相等的最小操作次数
        return int(any(x != nums[0] for x in nums))  # 存在不同元素返回 1，全部相同返回 0
