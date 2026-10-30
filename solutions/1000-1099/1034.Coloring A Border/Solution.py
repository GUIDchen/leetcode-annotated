# 题目：1034. 边界着色（Coloring A Border）
# 思路：从 (row, col) 做 DFS 遍历同色连通块；某格若贴矩阵边界或存在异色邻居即连通块边界，涂成 color。
# 时间复杂度：O(m*n)，每格最多访问一次；空间复杂度：O(m*n)，访问标记与递归栈。
class Solution:  # LeetCode 约定的题解类
    def colorBorder(  # 把 (row, col) 所在同色连通块的边界格涂成 color，返回原地修改后的矩阵
        self, grid: List[List[int]], row: int, col: int, color: int  # 参数续行：grid 矩阵、row/col 起点、color 目标颜色
    ) -> List[List[int]]:  # 参数续行结束，返回二维矩阵
        def dfs(i: int, j: int, c: int) -> None:  # 内嵌递归函数：i、j 当前格，c 为该连通块原来的颜色
            vis[i][j] = True  # 进入即标记已访问，避免同一格被反复递归
            for a, b in pairwise((-1, 0, 1, 0, -1)):  # pairwise 把方向元组两两配对成 (行偏移, 列偏移)
                x, y = i + a, j + b  # 计算相邻格坐标
                if 0 <= x < m and 0 <= y < n:  # 相邻格仍在矩阵内
                    if not vis[x][y]:  # 相邻格还没被访问过
                        if grid[x][y] == c:  # 颜色相同说明属于同一个连通块
                            dfs(x, y, c)  # 继续深搜该区域
                        else:  # 否则相邻格是异色（或已改色）
                            grid[i][j] = color  # 当前格紧邻异色块，属于边界，重新着色
                else:  # 否则越界，当前格贴着矩阵外边框
                    grid[i][j] = color  # 贴边同样算边界，重新着色

        m, n = len(grid), len(grid[0])  # 行数与列数（内嵌函数通过闭包读取）
        vis = [[False] * n for _ in range(m)]  # 访问标记表，先全部建成 False
        dfs(row, col, grid[row][col])  # 从起点深搜，原始颜色取起点格的颜色（必须先取，否则会被改色破坏）
        return grid  # 返回原地修改后的矩阵
