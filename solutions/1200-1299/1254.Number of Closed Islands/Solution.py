# 题目：1254. 统计封闭岛屿的数目（Number of Closed Islands）
# 思路：从每个尚未访问的陆地格出发做 DFS，把整座岛淹掉（置 1）；DFS 途中若碰到矩阵边界就说明这座岛不封闭，用按位与把该岛的答案置 0。
# 时间复杂度：O(mn)，每个格子最多被访问一次；空间复杂度：O(mn)，递归栈最坏深度为格子总数。
class Solution:  # LeetCode 约定的题解类
    def closedIsland(self, grid: List[List[int]]) -> int:  # grid：0 表示陆地、1 表示水；返回四周都被水包围的岛屿个数
        def dfs(i: int, j: int) -> int:  # 内层 DFS：淹掉与 (i, j) 连通的整座岛，并返回这座岛是否封闭（1/0）
            res = int(0 < i < m - 1 and 0 < j < n - 1)  # 不在最外圈记 1（可能封闭），在边界上记 0；int() 把布尔值转成 0/1
            grid[i][j] = 1  # 把当前格改为水，相当于标记已访问，避免重复搜索与死循环
            for a, b in pairwise(dirs):  # pairwise 把方向序列两两配对，得到 (-1,0) (0,1) (1,0) (0,-1) 四个方向
                x, y = i + a, j + b  # 相邻格坐标：a 是行偏移，b 是列偏移
                if 0 <= x < m and 0 <= y < n and grid[x][y] == 0:  # 相邻格在界内且仍是陆地时继续深搜
                    res &= dfs(x, y)  # 按位与：只要有一座相邻子岛不封闭，整座岛就不封闭
            return res  # 返回整座岛是否封闭（1 表示封闭，0 表示不封闭）

        m, n = len(grid), len(grid[0])  # 取行数与列数；放在 dfs 之后定义，调用时已完成赋值，闭包能取到
        dirs = (-1, 0, 1, 0, -1)  # 方向序列，配合 pairwise 可循环走完四个方向
        return sum(grid[i][j] == 0 and dfs(i, j) for i in range(m) for j in range(n))  # 只从未被访问的陆地出发搜索，dfs 返回 1 才计一次；边界上的回溯值会自然为 0
