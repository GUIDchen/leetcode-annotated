# 题目：1428. 至少有一个 1 的最左端列（Leftmost Column with at Least a One）
# 思路：每行都是非递减的 0/1 序列，用 bisect_left 按「该列是否为 1」二分出每行最左的 1，再取最小值。
# 时间复杂度：O(m log n)，m 行各二分一次；空间复杂度：O(1)，只用常数个变量。
# """
# This is BinaryMatrix's API interface.
# You should not implement it, or speculate about its implementation
# """
# class BinaryMatrix(object):
#    def get(self, row: int, col: int) -> int:
#    def dimensions(self) -> list[]:


class Solution:  # LeetCode 约定的题解类
    def leftMostColumnWithOne(self, binaryMatrix: "BinaryMatrix") -> int:  # binaryMatrix 是题目给的只读接口，只能通过 get/dimensions 访问
        m, n = binaryMatrix.dimensions()  # dimensions() 返回 (行数, 列数)
        ans = n  # 答案初值取 n，表示「目前还没找到任何 1」
        for i in range(m):  # 每一行单独二分，找该行最左的 1
            j = bisect_left(range(n), 1, key=lambda k: binaryMatrix.get(i, k))  # 在 [0, n) 上以「该列是否为 1」为键二分，返回第一个 1 的列下标
            ans = min(ans, j)  # 所有行的结果取最小列号
        return -1 if ans >= n else ans  # ans 仍为 n 说明整张矩阵没有 1，按题意返回 -1
