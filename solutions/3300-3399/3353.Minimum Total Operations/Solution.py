# 题目：3353. 最小总操作数（Minimum Total Operations）
# 思路：一次操作可以给一段区间同时加同一个数，把相邻且相等的元素并成一组最省，答案就是相邻不相等的对数。
# 时间复杂度：O(n)，遍历一遍数组；空间复杂度：O(1)，只用一个求和表达式。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int]) -> int:  # nums：输入数组
        return sum(x != y for x, y in pairwise(nums))  # pairwise 生成相邻二元组，True 计为 1，求和即相邻不相等的对数，也就是最少操作数
