# 题目：2482. 行和列中一和零的差值（Difference Between Ones and Zeros in Row and Column）
# 思路：先统计每行、每列的 1 的个数，再对每个格子用 ones(i)+ones(j)-zeros(i)-zeros(j) 计算差值，其中 zeros 由长度减 ones 得到。
# 时间复杂度：O(m·n)，两遍扫描矩阵；空间复杂度：O(m·n)，结果矩阵之外还有 O(m+n) 的行列计数。
class Solution:  # LeetCode 约定的题解类
    def onesMinusZeros(self, grid: List[List[int]]) -> List[List[int]]:  # grid：m×n 的 0/1 矩阵；返回同尺寸的差值矩阵
        m, n = len(grid), len(grid[0])  # 行数与列数
        rows = [0] * m  # rows[i]：第 i 行 1 的个数
        cols = [0] * n  # cols[j]：第 j 列 1 的个数
        for i, row in enumerate(grid):  # 遍历每一行及其下标
            for j, v in enumerate(row):  # 遍历该行每一列的值
                rows[i] += v  # 是 1 就累加进行计数
                cols[j] += v  # 同时累加进列计数
        diff = [[0] * n for _ in range(m)]  # 结果矩阵，m 行 n 列，先全部置 0
        for i, r in enumerate(rows):  # 遍历每行 1 的个数 r
            for j, c in enumerate(cols):  # 遍历每列 1 的个数 c
                diff[i][j] = r + c - (n - r) - (m - c)  # 行、列的 1 的个数减去各自 0 的个数（zeros = 长度 - ones）
        return diff  # 返回差值矩阵
