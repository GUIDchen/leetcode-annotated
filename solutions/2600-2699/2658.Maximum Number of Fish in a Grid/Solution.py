# 题目：2658. 网格图中鱼的最大数目（Maximum Number of Fish in a Grid）
# 核心思路：把非 0 格子看成水域，用 DFS 求每个连通块的鱼数之和，访问后置 0 标记，取所有连通块的最大值。
# 时间复杂度：O(m*n)，每个格子最多访问一次；空间复杂度：O(m*n)，递归栈最坏深度。
class Solution:  # 题解类
    def findMaxFish(self, grid: List[List[int]]) -> int:  # grid：渔网网格，值为鱼的数量，0 表示陆地；返回一次能捕到的最大鱼数
        def dfs(i: int, j: int) -> int:  # 定义内层递归函数：求 (i, j) 所在连通块的鱼总数
            cnt = grid[i][j]  # 先取走当前格子的鱼
            grid[i][j] = 0  # 置 0 标记已访问，避免重复计数与无限递归
            for a, b in pairwise((-1, 0, 1, 0, -1)):  # 相邻配对得到 (-1,0)、(0,1)、(1,0)、(0,-1) 四个方向
                x, y = i + a, j + b  # 计算相邻格子的坐标
                if 0 <= x < m and 0 <= y < n and grid[x][y]:  # 未越界且是水域
                    cnt += dfs(x, y)  # 递归累加该方向的鱼数
            return cnt  # 返回整个连通块的鱼总数

        m, n = len(grid), len(grid[0])  # 初始化 m 行 n 列；dfs 内部要引用，故必须先定义
        ans = 0  # 记录最大鱼数
        for i in range(m):  # 枚举每一行
            for j in range(n):  # 枚举每一列
                if grid[i][j]:  # 发现尚未访问的水域，即新的连通块
                    ans = max(ans, dfs(i, j))  # 用该连通块的鱼数更新答案
        return ans  # 返回最大鱼数
