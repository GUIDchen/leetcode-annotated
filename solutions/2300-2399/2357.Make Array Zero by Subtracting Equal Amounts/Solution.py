# 题目：2357. 使数组中所有元素都等于零（Make Array Zero by Subtracting Equal Amounts）
# 思路：每次操作都减去当前最小非零值，因此答案等于不同非零值的个数；集合推导式一步完成去重与剔除 0。
# 时间复杂度：O(n)，构造集合一遍扫描；空间复杂度：O(n)，最坏情况下集合存 n 个不同的非零值。
class Solution:  # LeetCode 约定的题解类
    def minimumOperations(self, nums: List[int]) -> int:  # nums 是输入数组，返回最少操作次数
        return len({x for x in nums if x})  # 集合推导式去重并跳过 0，其大小就是不同的非零值个数
