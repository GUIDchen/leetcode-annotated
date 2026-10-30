# 题目：2639. 查询网格图中每一列的宽度（Find the Width of Columns of a Grid）
# 思路：用 zip(*grid) 把网格按列转置，再对每一列求「数字字符串长度」的最大值。
# 时间复杂度：O(m * n * L)，L 为单个数字的位数；空间复杂度：O(n)，保存每列答案。
class Solution:  # LeetCode 约定的题解类
    def findColumnWidth(self, grid: List[List[int]]) -> List[int]:  # grid 是 m 行 n 列的整数网格
        return [max(len(str(x)) for x in col) for col in zip(*grid)]  # 转置后逐列求最大宽度；str 自带负号，len 即宽度
