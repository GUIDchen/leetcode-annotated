# 题目：2441. 与对应负数同时存在的最大正整数（Largest Positive Integer That Exists With Its Negative）【简单】
# 思路：用集合去重并支持 O(1) 查找，再用生成器筛出「自身与相反数都在集合里」的数取最大值；筛不出时由 default=-1 给出题面要求的 -1。
# 时间复杂度：O(n)，建集合 O(n)、筛选并取最大 O(n)；空间复杂度：O(n)，集合最多存 n 个不同值。
class Solution:  # LeetCode 约定的题解类
    def findMaxK(self, nums: List[int]) -> int:  # nums 是输入数组
        s = set(nums)  # 转成集合：既去重，又让 -x in s 的查询变成 O(1)
        return max((x for x in s if -x in s), default=-1)  # 生成器只产出相反数也在集合中的数，max 取其中最大；没有候选时返回 default=-1
