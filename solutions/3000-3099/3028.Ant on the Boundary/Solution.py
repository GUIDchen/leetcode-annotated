# 题目：3028. 边界上的蚂蚁（Ant on the Boundary）
# 思路：用 accumulate 惰性生成全部前缀和，也就是蚂蚁每一步之后的位置，统计其中等于 0 的个数即可。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，accumulate 是迭代器，只保存当前累加值。
class Solution:  # LeetCode 约定的题解类
    def returnToBoundaryCount(self, nums: List[int]) -> int:  # nums：每一步的位移数组，正右负左
        return sum(s == 0 for s in accumulate(nums))  # 前缀和 s 等于 0 说明此刻回到边界，sum 统计这种步数
