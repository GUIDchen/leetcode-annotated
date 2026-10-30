# 题目：2918. 数组的最小相等和（Minimum Equal Sum of Two Arrays After Replacing Zeros）
# 思路：元素和加上 0 的个数，就是把所有 0 替换成 1 后的最小和；令 s1<=s2，相等返回 s1，否则只有 nums1 含 0 才能把和抬到 s2。
# 时间复杂度：O(n+m)，sum 与 count 各扫一遍；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minSum(self, nums1: List[int], nums2: List[int]) -> int:  # nums1、nums2：两个可以把 0 替换为正整数的数组
        s1 = sum(nums1) + nums1.count(0)  # 元素和 + 0 的个数 = 所有 0 都替换成 1 后的最小和
        s2 = sum(nums2) + nums2.count(0)  # 同理算出 nums2 能取到的最小和
        if s1 > s2:  # 保证 s1 是较小的那个和，后面只需朝一个方向讨论
            return self.minSum(nums2, nums1)  # 交换两个数组递归，复用同一套判断
        if s1 == s2:  # 两数组最小和已经相等
            return s1  # 这个和就是答案
        return -1 if nums1.count(0) == 0 else s2  # s1<s2 时只有 nums1 含 0 才能把和上调到 s2，否则无解
