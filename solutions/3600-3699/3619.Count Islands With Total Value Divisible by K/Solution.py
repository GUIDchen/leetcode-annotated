# 3619. Count Islands With Total Value Divisible by K / 总价值可以被 K 整除的岛屿数目
# 核心思路：网格 DFS 洪水填充，每次从一块未访问的陆地出发累加整座岛的价值并把格子清零，若总和能被 k 整除就计数。
# 复杂度：时间复杂度 O(m * n)，空间复杂度 O(m * n)，m、n 分别为网格的行数与列数。
class Solution:  # 定义题解类
    def countIslands(self, grid: List[List[int]], k: int) -> int:  # 统计总价值能被 k 整除的岛屿数量
        def dfs(i: int, j: int) -> int:  # 递归函数：从 (i, j) 出发淹没整座岛并返回其总价值
            s = grid[i][j]  # 先累加当前格子的价值
            grid[i][j] = 0  # 把当前格子置 0，充当已访问标记
            for a, b in pairwise(dirs):  # 用方向数组的相邻两项遍历四个方向
                x, y = i + a, j + b  # 算出相邻格子的坐标
                if 0 <= x < m and 0 <= y < n and grid[x][y]:  # 邻格在界内且仍有价值才继续深入
                    s += dfs(x, y)  # 递归累加邻格所在整块的价值
            return s  # 返回这座岛的总价值

        m, n = len(grid), len(grid[0])  # 行数 m、列数 n
        dirs = (-1, 0, 1, 0, -1)  # 方向数组：首尾相同，配合 pairwise 得到四个方向
        ans = 0  # ans 记录满足条件的岛屿数量
        for i in range(m):  # 逐行扫描
            for j in range(n):  # 逐列扫描
                if grid[i][j] and dfs(i, j) % k == 0:  # 遇到未访问的陆地就淹没它，并判断其总价值能否被 k 整除
                    ans += 1  # 能整除则计数加一
        return ans  # 返回岛屿数量
