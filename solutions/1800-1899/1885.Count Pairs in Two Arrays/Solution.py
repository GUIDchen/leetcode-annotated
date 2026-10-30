# 题目：1885. 统计数对（Count Pairs in Two Arrays）
# 思路：把 nums1[i]+nums1[j] > nums2[i]+nums2[j] 化为差值数组上的 nums[i]+nums[j] > 0，排序后用双指针计数。
# 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(n)，差值数组。
class Solution:  # LeetCode 约定的题解类
    def countPairs(self, nums1: List[int], nums2: List[int]) -> int:  # nums1、nums2 是两个等长数组
        nums = [a - b for a, b in zip(nums1, nums2)]  # 逐位求差，把原条件化简为两数之和大于 0
        nums.sort()  # 升序排序，使差值单调，便于双指针
        l, r = 0, len(nums) - 1  # 左右指针分别指向最小值和最大值
        ans = 0  # 累加合法数对数量
        while l < r:  # 固定右端点 r，找满足条件的最左端点 l
            while l < r and nums[l] + nums[r] <= 0:  # 两数之和不够大就右移左指针
                l += 1  # 丢弃更小的左值
            ans += r - l  # l..r-1 之间的下标都能与 r 组成合法数对
            r -= 1  # 右端点左移，处理下一组
        return ans  # 返回数对总数
