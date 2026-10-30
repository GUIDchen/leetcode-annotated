# 题目：2956. 找到两个数组中的公共元素（Find Common Elements Between Two Arrays）
# 思路：把两个数组分别转成集合，利用集合 O(1) 的查询分别统计每个元素是否在对方数组中出现过。
# 时间复杂度：O(n + m)，两次集合构造加两次线性统计；空间复杂度：O(n + m)，两个集合的大小。
class Solution:  # LeetCode 约定的题解类
    def findIntersectionValues(self, nums1: List[int], nums2: List[int]) -> List[int]:  # nums1、nums2 是输入数组，返回两个计数组成的列表
        s1, s2 = set(nums1), set(nums2)  # 建立两个集合，用于 O(1) 判断某个值是否出现过
        return [sum(x in s2 for x in nums1), sum(x in s1 for x in nums2)]  # 分别统计 nums1 中能在 nums2 找到的个数、nums2 中能在 nums1 找到的个数
