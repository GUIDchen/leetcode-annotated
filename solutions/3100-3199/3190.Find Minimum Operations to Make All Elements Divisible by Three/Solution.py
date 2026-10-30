# 题目：3190. 使所有元素都可以被 3 整除的最少操作数（Find Minimum Operations to Make All Elements Divisible by Three）
# 思路：用生成器统计「不能被 3 整除」的元素个数；每个这样的元素只需一次 +1 或 -1 就能变成 3 的倍数。
# 时间复杂度：O(n)，遍历数组一次；空间复杂度：O(1)，只保留一个累加结果。
class Solution:  # LeetCode 约定的题解类
    def minimumOperations(self, nums: List[int]) -> int:  # nums：输入的整数数组，返回最少操作次数
        return sum(x % 3 != 0 for x in nums)  # 布尔值参加求和时 True 计 1、False 计 0，和就是答案
