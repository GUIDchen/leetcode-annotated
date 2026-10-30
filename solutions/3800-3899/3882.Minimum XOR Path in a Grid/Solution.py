# 3882. 网格图中最小异或路径 / Minimum XOR Path in a Grid
# 核心思路：按最大值的二进制位数确定异或值上界，用三维布尔 DP 记录每格可达的异或值，最后取终点最小值。
# 复杂度：时间 O(m * n * 2^b)，空间 O(m * n * 2^b)。
class Solution:  # 定义题解类
    def minCost(self, grid: list[list[int]]) -> int:  # 返回最小异或路径值
        m, n = len(grid), len(grid[0])  # 网格行数与列数
        mx = 1 << (max(max(row) for row in grid)).bit_length()  # 异或值上界：不小于最大值的 2 的幂
        f = [[[False] * mx for _ in range(n)] for _ in range(m)]  # f[i][j][k] 表示走到 (i, j) 能否得到异或值 k
        f[0][0][grid[0][0]] = True  # 起点异或值只含起点自身的值
        for i, row in enumerate(grid):  # 枚举行
            for j, x in enumerate(row):  # 枚举列与当前格子的值
                if i > 0 or j > 0:  # 起点已初始化，跳过
                    for k in range(mx):  # 枚举目标异或值
                        if i > 0 and f[i - 1][j][k ^ x]:  # 从上方转移：上一步异或值须为 k ^ x
                            f[i][j][k] = True  # 标记该异或值可达
                        if j > 0 and f[i][j - 1][k ^ x]:  # 从左方转移：左一步异或值须为 k ^ x
                            f[i][j][k] = True  # 标记该异或值可达
        return next(k for k in range(mx) if f[m - 1][n - 1][k])  # 返回终点的最小可达异或值
