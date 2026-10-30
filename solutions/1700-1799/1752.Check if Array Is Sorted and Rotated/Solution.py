# 题目：1752. 检查数组是否经排序和轮转得到（Check if Array Is Sorted and Rotated）
# 核心思路：按环形顺序统计相邻元素「前一个大于后一个」的次数，排序后轮转的数组至多出现一次下降。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只使用求和计数器。
class Solution:  # LeetCode 约定的题解类
    def check(self, nums: List[int]) -> bool:  # nums 是输入数组，返回是否为排序后轮转得到的数组
        return sum(nums[i - 1] > x for i, x in enumerate(nums)) <= 1  # i - 1 取到 -1 时正好指向最后一个元素，实现首尾相接的环形比较；下降次数 ≤ 1 才合法
