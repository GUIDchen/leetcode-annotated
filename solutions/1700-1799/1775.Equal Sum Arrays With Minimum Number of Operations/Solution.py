# 题目：1775. 通过最少操作次数使数组的和相等（Equal Sum Arrays With Minimum Number of Operations）
# 思路：交换两个数组使 s1 < s2，收集每个元素的最大可改变量（小的一侧 6-v、大的一侧 v-1）并降序排序，贪心先做收益最大的操作直到差值补齐。
# 时间复杂度：O((n+m) log (n+m))，排序开销；空间复杂度：O(n+m) 存放改变量。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums1: List[int], nums2: List[int]) -> int:  # nums1/nums2：两个元素取值都在 1..6 的数组
        s1, s2 = sum(nums1), sum(nums2)  # 分别求两个数组的元素和
        if s1 == s2:  # 已经相等
            return 0  # 不需要任何操作
        if s1 > s2:  # 保证 s1 是较小的那个和
            return self.minOperations(nums2, nums1)  # 交换参数，复用同一套逻辑
        arr = [6 - v for v in nums1] + [v - 1 for v in nums2]  # 每个元素最多能贡献的改变量
        d = s2 - s1  # 需要弥补的差值
        for i, v in enumerate(sorted(arr, reverse=True), 1):  # 按贡献从大到小使用，i 从 1 开始计操作次数
            d -= v  # 用当前操作缩小差值
            if d <= 0:  # 差值补齐
                return i  # 返回已使用的操作数
        return -1  # 全部用上仍无法相等
