# 题目：200. 岛屿数量（Number of Islands）
# 思路：扫描网格，遇到 '1' 就以它为起点 DFS，把连通的一整块陆地改成 '0'（原地染色），同时岛屿计数加一。
# 时间复杂度：O(mn)，每个格子最多被访问一次；空间复杂度：O(mn)，最坏情况递归栈深度。
class Solution:  # LeetCode 约定的题解类
    def numIslands(self, grid: List[List[str]]) -> int:  # grid：由 '1' 和 '0' 组成的二维网格；返回岛屿数量
        def dfs(i, j):  # dfs(i, j)：把 (i, j) 所在的整块连通陆地全部染成 '0'（闭包捕获 m、n、dirs 与 grid）
            grid[i][j] = '0'  # 先淹掉当前格子，既是染色也是访问标记，避免重复或死循环
            for a, b in pairwise(dirs):  # pairwise 把方向数组拆成 (dx, dy) 两两一组，正好对应四个方向
                x, y = i + a, j + b  # 相邻格子的坐标
                if 0 <= x < m and 0 <= y < n and grid[x][y] == '1':  # 在网格范围内且该格子是尚未访问的陆地
                    dfs(x, y)  # 继续深搜，最终整块陆地都会被清空

        ans = 0  # 岛屿计数器
        dirs = (-1, 0, 1, 0, -1)  # 方向数组：相邻两项拼成一个方向向量
        m, n = len(grid), len(grid[0])  # 行数与列数
        for i in range(m):  # 逐行扫描
            for j in range(n):  # 逐列扫描
                if grid[i][j] == '1':  # 发现未被访问的陆地，说明遇到一座新岛屿
                    dfs(i, j)  # DFS 把这座岛整体淹没
                    ans += 1  # 岛屿计数加一
        return ans  # 返回岛屿总数
