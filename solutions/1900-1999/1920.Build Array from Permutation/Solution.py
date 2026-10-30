# 题目：1920. 基于排列构建数组（Build Array from Permutation）
# 思路：列表推导式一次完成映射，ans[i] = nums[nums[i]]。
# 时间复杂度：O(n)；空间复杂度：O(n)，为新构造的结果列表。
class Solution:  # LeetCode 约定的题解类
    def buildArray(self, nums: List[int]) -> List[int]:  # nums 是 0~n-1 的排列，返回按 ans[i] = nums[nums[i]] 构造的新列表
        return [nums[num] for num in nums]  # 列表推导式：对每个 num 取出 nums[num] 组成结果列表
