# 题目：1818. 绝对差值和（Minimum Absolute Sum Difference）
# 思路：先算出原始绝对差总和 s；把 nums1 排序后，对每个位置二分找最接近 nums2[i] 的值，求出能减少的最大差值 mx，答案是 (s - mx) mod 1e9+7。
# 时间复杂度：O(n log n)，排序加上 n 次二分；空间复杂度：O(n)，保存 nums1 的排序副本。
class Solution:  # LeetCode 约定的题解类
    def minAbsoluteSumDiff(self, nums1: List[int], nums2: List[int]) -> int:  # nums1、nums2：两个等长数组
        mod = 10**9 + 7  # 题目要求的取模值
        nums = sorted(nums1)  # nums1 的升序副本，供二分查找使用
        s = sum(abs(a - b) for a, b in zip(nums1, nums2)) % mod  # 原始绝对差总和（先取模）
        mx = 0  # 记录替换某一个元素后绝对差可能减少的最大值
        for a, b in zip(nums1, nums2):  # 逐对枚举位置上的 nums1[i] 与 nums2[i]
            d1, d2 = abs(a - b), inf  # d1 是当前绝对差；d2 是替换后能达到的最小绝对差
            i = bisect_left(nums, b)  # 二分找第一个 >= b 的下标
            if i < len(nums):  # 存在右侧候选值 nums[i]
                d2 = min(d2, abs(nums[i] - b))  # 用右侧较近的值更新最小绝对差
            if i:  # 存在左侧候选值 nums[i-1]
                d2 = min(d2, abs(nums[i - 1] - b))  # 用左侧较近的值更新最小绝对差
            mx = max(mx, d1 - d2)  # 该位置替换后能减少的差值，取全局最大
        return (s - mx + mod) % mod  # 总和减去最大可减少量，加 mod 防止出现负数
