# 题目：2089. 找出数组排序后的目标下标（Find Target Indices After Sorting Array）
# 思路：原地升序排序后，所有等于 target 的元素必然连续出现，用列表推导式一次性收集它们的下标，结果天然升序。
# 时间复杂度：O(n log n)，主要开销是排序；空间复杂度：O(1)（不计返回的列表）。
class Solution:  # LeetCode 约定的题解类
    def targetIndices(self, nums: List[int], target: int) -> List[int]:  # nums：待排序数组；target：目标值；返回所有等于 target 的下标（升序）
        nums.sort()  # 原地升序排序，让相同的值聚集在一起
        return [i for i, v in enumerate(nums) if v == target]  # 遍历 (下标, 元素)，只挑出值等于 target 的下标组成新列表返回
