# 题目：1905. 统计子岛屿（Count Sub Islands）
# 思路：对 grid2 做 DFS 找连通块，块内每个格子都必须在 grid1 中是陆地，整块才算子岛屿；访问过的格子原地置 0 当作 visited。
# 时间复杂度：O(m·n)，每个格子最多访问一次；空间复杂度：O(m·n)，递归栈最坏深度。
class Solution:  # LeetCode 约定的题解类
    def countSubIslands(self, grid1: List[List[int]], grid2: List[List[int]]) -> int:  # grid1：原图；grid2：待判定的图
        def dfs(i: int, j: int) -> int:  # 递归函数：从 (i, j) 出发标记整块陆地，返回 1 表示它完全位于 grid1 的陆地中
            ok = grid1[i][j]  # 当前位置在 grid1 中是否也是陆地
            grid2[i][j] = 0  # 置 0 表示已访问，防止重复递归
            for a, b in pairwise(dirs):  # pairwise 把方向序列两两配对，得到四个方向的 (行增量, 列增量)
                x, y = i + a, j + b  # 邻居坐标
                if 0 <= x < m and 0 <= y < n and grid2[x][y] and not dfs(x, y):  # 邻居在界内、未访问，且该邻居所在的整块也不是子岛屿时，当前块同样不是
                    ok = 0  # 只要有一格不满足，整座岛就不是子岛屿
            return ok  # 返回这块陆地的判定结果

        m, n = len(grid1), len(grid1[0])  # 行列数（dfs 真正调用时才会读取，所以可以写在它后面）
        dirs = (-1, 0, 1, 0, -1)  # 四方向偏移
        return sum(dfs(i, j) for i in range(m) for j in range(n) if grid2[i][j])  # 遇到未访问的陆地就做一次 DFS，把是子岛屿的计数累加
