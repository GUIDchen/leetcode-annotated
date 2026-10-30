# 题目：462. 最小操作次数使数组元素相等 II（Minimum Moves to Equal Array Elements II）
# 思路：排序后取中位数作为目标值；各元素到中位数的绝对距离之和即最小操作次数。
# 时间复杂度：O(n log n)（排序）；空间复杂度：O(1)（不计排序自身开销）。
class Solution:  # LeetCode 约定的题解类
    def minMoves2(self, nums: List[int]) -> int:  # nums 是整数数组，返回把所有元素变成同一个值的最小操作次数
        nums.sort()  # 先排序，才能取到中位数
        k = nums[len(nums) >> 1]  # 取中间位置的值作为目标（len(nums) >> 1 等价于整除 2）
        return sum(abs(v - k) for v in nums)  # 各元素与中位数的距离之和即为最小操作次数
