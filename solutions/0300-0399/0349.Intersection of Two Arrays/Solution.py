# 题目：349. 两个数组的交集（Intersection of Two Arrays）
# 思路：把两个数组分别转成集合，用 & 求交集一次去重，再转回列表输出。
# 时间复杂度：O(n + m)，集合构建与求交各是线性；空间复杂度：O(n + m)，两个集合的额外存储。
class Solution:  # LeetCode 约定的题解类
    def intersection(self, nums1: List[int], nums2: List[int]) -> List[int]:  # nums1、nums2：两个输入数组；返回交集元素（唯一且顺序不限）
        return list(set(nums1) & set(nums2))  # set 自动去重，& 求两个集合的交集，末尾 list() 把结果转回题目要求的列表类型
