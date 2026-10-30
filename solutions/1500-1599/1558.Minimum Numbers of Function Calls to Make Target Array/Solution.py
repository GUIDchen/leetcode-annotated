# 题目：1558. 得到目标数组的最少函数调用次数（Minimum Numbers of Function Calls to Make Target Array）
# 思路：每个数的二进制 1 的个数是要单独加 1 的次数，所有数一起乘 2 的次数等于最大值的二进制位数减一。
# 时间复杂度：O(n)，n 为数组长度；空间复杂度：O(1)，只做位运算与求和。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int]) -> int:  # nums：目标数组
        return sum(v.bit_count() for v in nums) + max(0, max(nums).bit_length() - 1)  # 所有元素二进制中 1 的个数之和 + 最大值的二进制位数减一（整体乘 2 的次数）
