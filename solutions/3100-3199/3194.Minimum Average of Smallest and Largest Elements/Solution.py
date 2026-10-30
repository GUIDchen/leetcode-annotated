# 题目：3194. 最小元素和最大元素的最小平均值（Minimum Average of Smallest and Largest Elements）
# 思路：排序后固定「最小配最大」，只需在前一半配对中找两数之和的最小值，最后除以 2 即最小平均值。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，排序外只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimumAverage(self, nums: List[int]) -> float:  # nums：输入整数数组，返回最小平均值
        nums.sort()  # 原地升序排序，方便小值与大值配对
        n = len(nums)  # 数组长度，用于取对称下标
        return min(nums[i] + nums[-i - 1] for i in range(n // 2)) / 2  # 前一半配对里取最小和，再除以 2 得到平均值
