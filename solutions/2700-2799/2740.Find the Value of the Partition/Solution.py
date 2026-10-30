# 题目：2740. 找出分区值（Find the Value of the Partition）
# 核心思路：排序后最优划分一定切在相邻两个元素之间，答案是相邻元素差的最小值。
# 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(log n)，排序的递归栈开销。
class Solution:  # LeetCode 约定的题解类
    def findValueOfPartition(self, nums: List[int]) -> int:  # nums：待划分的正整数数组
        nums.sort()  # 原地升序排序，让数值相近的元素相邻
        return min(b - a for a, b in pairwise(nums))  # pairwise 依次取出每一对相邻元素，返回最小差值
