# 题目：453. 最小操作次数使数组元素相等（Minimum Moves to Equal Array Elements）
# 思路：每次把 n-1 个元素加一，等价于每次把 1 个元素减一；要让全部元素相等只能都降到最小值，故答案为「总和 - 最小值 × n」。
# 时间复杂度：O(n)，求和与求最小值各扫一遍；空间复杂度：O(1)，只用内置函数，不额外开数组。
class Solution:  # LeetCode 约定的题解类
    def minMoves(self, nums: List[int]) -> int:  # nums：长度至少为 1 的整数数组；返回使所有元素相等的最少操作次数
        return sum(nums) - min(nums) * len(nums)  # 等价于每次只把一个元素减一，因此答案为把所有元素降到最小值所需的总步数
