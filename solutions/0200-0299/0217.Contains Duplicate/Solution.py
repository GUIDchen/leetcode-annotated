# 题目：217. 存在重复元素（Contains Duplicate）
# 核心思路：先排序，再用 pairwise 取相邻对，只要有一对相等就说明存在重复元素。
# 时间复杂度：O(n log n)，排序为主开销；空间复杂度：O(n)，排序产生的临时列表。
class Solution:  # LeetCode 约定的题解类
    def containsDuplicate(self, nums: List[int]) -> bool:  # 判断数组中是否存在重复元素
        return any(a == b for a, b in pairwise(sorted(nums)))  # 先排序，再遍历相邻对：只要存在一对相等就返回 True
