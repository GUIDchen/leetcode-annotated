# 题目：931. 下降路径最小和（Minimum Falling Path Sum）
# 思路：按行动态规划。f[j] 是落到上一行第 j 列的最小和，当前格取左上、正上、右上三者的最小值再加自身。
# 时间复杂度：O(n^2)，n 行 n 列各算一次；空间复杂度：O(n)，只保留上一行与当前行两个一维数组。
class Solution:  # LeetCode 约定的题解类
    def minFallingPathSum(self, matrix: List[List[int]]) -> int:  # matrix 是 n×n 矩阵，返回从第一行落到最后一行的最小路径和
        n = len(matrix)  # 矩阵边长
        f = [0] * n  # f[j]：到达上一行第 j 列的最小下降路径和；第一行上方视为 0
        for row in matrix:  # 自上而下逐行递推
            g = [0] * n  # 当前行的状态数组，默认 0
            for j, x in enumerate(row):  # 同时取出列号 j 与格子值 x
                l, r = max(0, j - 1), min(n, j + 2)  # 上一行可转移的列区间 [l, r)，对应左上、正上、右上三格，越界部分自动被截掉
                g[j] = min(f[l:r]) + x  # 三格取最小再加当前格子的值，就是到达 g[j] 的最小和
            f = g  # 当前行成为下一行的“上一行”
        return min(f)  # 最后一行的最小和就是答案
