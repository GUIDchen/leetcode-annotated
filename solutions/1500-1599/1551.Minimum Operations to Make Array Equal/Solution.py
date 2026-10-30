# 题目：1551. 使数组中所有元素相等的最小操作数（Minimum Operations to Make Array Equal）
# 思路：数组为 1,3,5,...,2n-1，每次操作让一对元素同时向中间各靠 1，总和不变所以目标值必为平均值 n；
# 时间复杂度：O(n)，只遍历左半部分 n/2 个元素；空间复杂度：O(1)，生成器表达式不额外开数组。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, n: int) -> int:  # n：数组长度（数组为前 n 个奇数）
        return sum(n - (i << 1 | 1) for i in range(n >> 1))  # 左半部分每个元素 2i+1 补齐到平均值 n 的差值总和
