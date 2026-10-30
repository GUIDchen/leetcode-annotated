# 题目：760. 找出变位映射（Find Anagram Mappings）
# 思路：先用字典记录 nums2 中「值 → 下标」，再按 nums1 顺序逐个查表生成映射数组。
# 时间复杂度：O(n)，两次线性遍历；空间复杂度：O(n)，字典与答案列表各存 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def anagramMappings(self, nums1: List[int], nums2: List[int]) -> List[int]:  # nums1 是待映射数组，nums2 是映射依据的排列
        d = {x: i for i, x in enumerate(nums2)}  # 字典推导：元素值 → 它在 nums2 中的下标
        return [d[x] for x in nums1]  # 按 nums1 的顺序查表，组成映射数组返回
