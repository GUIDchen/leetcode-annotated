# 题目：1913. 两个数对之间的最大乘积差（Maximum Product Difference Between Two Pairs）
# 思路：原地排序后，用最大两个数之积减去最小两个数之积，即为最大的乘积差。
# 时间复杂度：O(n log n)，来自一次排序；空间复杂度：O(1)，原地排序不额外分配线性空间。
class Solution:  # LeetCode 约定的题解类
    def maxProductDifference(self, nums: List[int]) -> int:  # nums：输入数组，至少 4 个正数
        nums.sort()  # 原地升序排序，最大值在后两个、最小值在前两个
        return nums[-1] * nums[-2] - nums[0] * nums[1]  # 最大两数之积减去最小两数之积
