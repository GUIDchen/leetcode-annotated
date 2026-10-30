# 题目：1568. 使陆地分离的最少天数（Minimum Number of Days to Disconnect Island）
# 思路：答案只可能是 0/1/2；先数连通块，已不是一块就返回 0，再尝试删掉每个陆地格子看能否分离，能则返回 1，否则返回 2。
# 时间复杂度：O(m^2 * n^2)，每个格子都做一次 O(mn) 的连通块统计；空间复杂度：O(mn)，递归深度与访问标记。
class Solution:  # LeetCode 约定的题解类
    def minDays(self, grid: List[List[int]]) -> int:  # grid：0/1 网格，1 表示陆地
        if self.count(grid) != 1:  # 一开始就不是完整的一块陆地
            return 0  # 不需要任何操作
        m, n = len(grid), len(grid[0])  # 网格的行数与列数
        for i in range(m):  # 枚举每一行
            for j in range(n):  # 枚举每一列
                if grid[i][j] == 1:  # 只尝试把陆地格子变成水
                    grid[i][j] = 0  # 试删这个格子
                    if self.count(grid) != 1:  # 删除后陆地不再是连通的一块
                        return 1  # 一天即可
                    grid[i][j] = 1  # 恢复现场，继续尝试下一个格子
        return 2  # 任何连通块都能靠删掉至多两个格子分离，故最多两天

    def count(self, grid):  # 统计网格中陆地连通块的个数
        def dfs(i, j):  # 从 (i, j) 出发标记整块陆地
            grid[i][j] = 2  # 标记为已访问
            for a, b in [[0, -1], [0, 1], [1, 0], [-1, 0]]:  # 上下左右四个方向
                x, y = i + a, j + b  # 邻居的坐标
                if 0 <= x < m and 0 <= y < n and grid[x][y] == 1:  # 邻居在界内且是未访问的陆地
                    dfs(x, y)  # 递归填充

        m, n = len(grid), len(grid[0])  # 网格尺寸，供内部 dfs 闭包使用
        cnt = 0  # 连通块计数
        for i in range(m):  # 遍历所有行
            for j in range(n):  # 遍历所有列
                if grid[i][j] == 1:  # 发现新的陆地
                    dfs(i, j)  # 填充整块陆地
                    cnt += 1  # 连通块数量加一
        for i in range(m):  # 还原访问标记
            for j in range(n):  # 遍历所有列
                if grid[i][j] == 2:  # 2 是 dfs 留下的访问标记
                    grid[i][j] = 1  # 改回陆地 1
        return cnt  # 返回连通块个数
