# 3667. Sort Array By Absolute Value（3667. 按绝对值排序数组）🔒
# 核心思路：以绝对值为排序键对数组升序排序。
# 复杂度：时间 O(n log n)，空间 O(n)。
class Solution:  # 定义题解类
    def sortByAbsoluteValue(self, nums: List[int]) -> List[int]:  # 按绝对值升序排列数组并返回
        return sorted(nums, key=lambda x: abs(x))  # 以绝对值为键排序并返回新列表
