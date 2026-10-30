# 题目：2328. 网格图中递增路径的数目（Number of Increasing Paths in a Grid）
# 思路：把每个格子当作路径起点，用记忆化 DFS 求「只走向严格更大邻居」的路径条数，
#       单格自身算 1 条，四方向累加取模，再对所有起点求和；时间 O(m×n)，空间 O(m×n)。
class Solution:  # LeetCode 约定的题解类
    def countPaths(self, grid: List[List[int]]) -> int:  # grid 是 m×n 的输入矩阵
        @cache  # 记忆化装饰器：缓存 dfs 的结果，同一状态只算一次（LeetCode 环境已提供，故源码未写 import）
        def dfs(i: int, j: int) -> int:  # 返回从 (i, j) 出发的递增路径条数
            ans = 1  # 单格自身也算一条路径，作为累加初值
            for a, b in pairwise((-1, 0, 1, 0, -1)):  # pairwise 把方向元组两两配对，依次得到上、右、下、左四个方向的增量
                x, y = i + a, j + b  # 邻居格子的坐标
                if 0 <= x < m and 0 <= y < n and grid[i][j] < grid[x][y]:  # 邻居不越界，且数值严格更大，路径才是递增的
                    ans = (ans + dfs(x, y)) % mod  # 以邻居为起点的路径都能接在当前步之后，累加并取模
            return ans  # 返回本格的路径总数（@cache 会自动保存）

# 下面的 mod、m、n 被 dfs 闭包引用；函数体在调用时才执行，所以可以放在定义之后
        mod = 10**9 + 7  # 结果取模的常量
        m, n = len(grid), len(grid[0])  # 矩阵的行数与列数
        return sum(dfs(i, j) for i in range(m) for j in range(n)) % mod  # 对所有格子作为起点的路径条数求和，取模后返回
