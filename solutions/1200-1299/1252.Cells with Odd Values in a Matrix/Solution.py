# 题目：1252. 奇数值单元格的数目（Cells with Odd Values in a Matrix）
# 思路：按题意直接开一个 m×n 矩阵，每个索引把对应整行与整列各加一，最后统计值为奇数的格子数。
# 时间复杂度：O(k(m+n)+mn)，k 为索引个数；空间复杂度：O(mn)，用于存放矩阵。
class Solution:  # LeetCode 约定的题解类
    def oddCells(self, m: int, n: int, indices: List[List[int]]) -> int:  # m 行 n 列；indices 中每个 [r, c] 表示第 r 行与第 c 列各加 1；返回值为奇数的格子数
        g = [[0] * n for _ in range(m)]  # 用推导式建一个 m×n 的棋盘，初值全 0；每行都是新建的列表，避免多行共享同一对象
        for r, c in indices:  # 逐条处理加一操作，拆出行号 r 与列号 c
            for i in range(m):  # 先把第 c 列整列加一
                g[i][c] += 1  # 列上第 i 行的格子加一
            for j in range(n):  # 再把第 r 行整行加一
                g[r][j] += 1  # 行上第 j 列的格子加一
        return sum(v % 2 for row in g for v in row)  # 生成器遍历所有格子，v % 2 为 1 即奇数，求和得到个数
