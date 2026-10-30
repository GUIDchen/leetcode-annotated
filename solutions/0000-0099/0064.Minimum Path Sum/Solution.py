# 题目：64. 最小路径和（Minimum Path Sum）
# 思路：二维 DP，f[i][j] 是到达 (i,j) 的最小路径和；第一行只能从左来、第一列只能从上来，其余格取两者较小值再加本格。
# 时间复杂度：O(m*n)，每格算一次；空间复杂度：O(m*n)，DP 表。
class Solution:  # LeetCode 约定的题解类
    def minPathSum(self, grid: List[List[int]]) -> int:  # grid：非负整数矩阵，从左上走到右下，只能向右或向下
        m, n = len(grid), len(grid[0])  # 行数、列数
        f = [[0] * n for _ in range(m)]  # DP 表，先全部置 0
        f[0][0] = grid[0][0]  # 起点没有前驱，路径和就是它自身的值
        for i in range(1, m):  # 填第一列
            f[i][0] = f[i - 1][0] + grid[i][0]  # 第一列只能从上方下来，直接累加
        for j in range(1, n):  # 填第一行
            f[0][j] = f[0][j - 1] + grid[0][j]  # 第一行只能从左方过来，直接累加
        for i in range(1, m):  # 其余行从上到下
            for j in range(1, n):  # 每行从左到右，保证上方与左方已算好
                f[i][j] = min(f[i - 1][j], f[i][j - 1]) + grid[i][j]  # 选较小的一条路径走过来，再加上本格代价
        return f[-1][-1]  # 返回右下角的最小路径和
