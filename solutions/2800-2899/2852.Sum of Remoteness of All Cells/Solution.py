# 题目：2852. 所有单元格的远离程度之和（Sum of Remoteness of All Cells）
# 核心思路：DFS 求每个连通块的石头总和 s 与格子数 t，块内每个格子对外只能到达其它块的 cnt - t 个格子，贡献 (cnt - t) * s。
# 时间复杂度：O(n^2)，每个格子只被访问一次；空间复杂度：O(n^2)，递归栈最深 n^2。
class Solution:  # LeetCode 约定的题解类
    def sumRemoteness(self, grid: List[List[int]]) -> int:  # grid 为 n x n 网格，-1 表示障碍，正数表示该格石头数
        def dfs(i: int, j: int) -> (int, int):  # 内层 dfs 返回 (连通块石头总和, 连通块格子数)
            s, t = grid[i][j], 1  # 当前格的石头数与格子数作为初值
            grid[i][j] = 0  # 清零相当于已访问标记，避免重复访问
            for a, b in pairwise(dirs):  # 相邻两项构成一个方向向量
                x, y = i + a, j + b  # 邻居坐标
                if 0 <= x < n and 0 <= y < n and grid[x][y] > 0:  # 邻居在界内且可通行才继续递归
                    s1, t1 = dfs(x, y)  # 递归统计邻居所在的连通块
                    s, t = s + s1, t + t1  # 把邻居的统计累加到当前块
            return s, t  # 返回本连通块的统计结果

        n = len(grid)  # 网格边长
        dirs = (-1, 0, 1, 0, -1)  # 方向数组
        cnt = sum(x > 0 for row in grid for x in row)  # 可通行格子的总数
        ans = 0  # 远离程度之和
        for i, row in enumerate(grid):  # 枚举每一行
            for j, x in enumerate(row):  # 枚举行内每一格
                if x > 0:  # 只从尚未访问的格子发起搜索
                    s, t = dfs(i, j)  # 统计当前连通块
                    ans += (cnt - t) * s  # 块内每个格子贡献 (cnt - t) * s
        return ans  # 返回答案
