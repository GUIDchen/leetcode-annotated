# 题目：3065. 超过阈值的最少操作数 I（Minimum Operations to Exceed Threshold Value I）
# 思路：每次操作只能删除一个元素，所以答案就是「小于 k 的元素个数」，用生成器求和一行搞定。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只累加计数。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int], k: int) -> int:  # nums 是输入数组，k 是阈值，返回需要删除的元素个数
        return sum(x < k for x in nums)  # x < k 为真的元素计 1，sum 得到小于阈值的元素总数
