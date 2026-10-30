# 题目：1020. 飞地的数量（Number of Enclaves）
# 思路：先从上下左右四条边界上的陆地出发做 DFS，把能连通到边界的陆地全部淹没成 0；剩余陆地即为飞地。
# 时间复杂度：O(m * n)，每个格子最多访问一次；空间复杂度：O(m * n)，递归深度最坏为格子总数。
class Solution:  # LeetCode 约定的题解类
    def numEnclaves(self, grid: List[List[int]]) -> int:  # grid：0/1 矩阵，1 是陆地、0 是海域；返回走不到边界的陆地格子数
        def dfs(i: int, j: int):  # 内部递归函数：把与 (i, j) 连通的一整块陆地淹没
            grid[i][j] = 0  # 先标记已访问（置 0），防止重复递归与死循环
            for a, b in pairwise(dirs):  # pairwise 把方向元组拆成连续的 (dx, dy) 对，正好覆盖四个方向
                x, y = i + a, j + b  # 计算邻居坐标
                if 0 <= x < m and 0 <= y < n and grid[x][y]:  # 越界检查，并且只在邻居是陆地（值为 1）时才继续
                    dfs(x, y)  # 递归淹没这个相邻陆地

        m, n = len(grid), len(grid[0])  # m 是行数、n 是列数；grid 非空所以 grid[0] 一定存在
        dirs = (-1, 0, 1, 0, -1)  # 方向偏移量：首尾重复，方便 pairwise 两两配对出四个方向
        # 第一步：从第 0 行与第 m-1 行这两条横向边界出发
        for j in range(n):  # 逐列扫描
            for i in (0, m - 1):  # 第 0 行与第 m-1 行分别是上、下边界
                if grid[i][j]:  # 边界格子是陆地才启动搜索
                    dfs(i, j)  # 淹没整块与上下边界连通的陆地
        # 第二步：从第 0 列与第 n-1 列这两条纵向边界出发
        for i in range(m):  # 逐行扫描
            for j in (0, n - 1):  # 第 0 列与第 n-1 列分别是左、右边界
                if grid[i][j]:  # 边界格子是陆地才启动搜索
                    dfs(i, j)  # 淹没整块与左右边界连通的陆地
        # 剩下的 1 全都无法连通到边界，直接对所有元素求和即为飞地数量
        return sum(sum(row) for row in grid)  # 逐行求和再累加
