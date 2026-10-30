# 题目：1219. 黄金矿工（Path with Maximum Gold）
# 思路：枚举每个非空格子作为起点做 DFS 回溯，进入时把格子清零表示已访问，四个方向取最大收益后恢复现场。
# 时间复杂度：最坏 O(m*n*4^(m*n))，相当于枚举所有简单路径；空间复杂度：O(m*n)，递归深度不超过格子总数。
class Solution:  # LeetCode 约定的题解类
    def getMaximumGold(self, grid: List[List[int]]) -> int:  # grid：矿网格，0 表示该格没有金子、不可停留
        def dfs(i: int, j: int) -> int:  # 内层函数：返回从 (i, j) 出发能挖到的最大金子数
            if not (0 <= i < m and 0 <= j < n and grid[i][j]):  # 越界、无金（0），或者已被本路径访问（也被置为 0），都无法继续采矿
                return 0  # 该方向收益为 0，直接返回
            v = grid[i][j]  # 先记住当前格子的金子数，稍后要恢复现场
            grid[i][j] = 0  # 置 0 表示已访问，避免同一条路径重复拿同一格的金子
            ans = max(dfs(i + a, j + b) for a, b in pairwise(dirs)) + v  # 用 pairwise 把 dirs 相邻两项配成一个方向 (a, b)，四个方向继续挖的最大收益再加当前格
            grid[i][j] = v  # 回溯：恢复格子的原始值，供其他路径作为起点时使用
            return ans  # 返回从 (i, j) 出发的最大收益

        m, n = len(grid), len(grid[0])  # 行列数；dfs 在调用时才读取闭包变量，所以可以先定义函数再定义 m、n
        dirs = (-1, 0, 1, 0, -1)  # 方向数组：下、右、上、左，相邻两项恰好组成一个 (dr, dc)
        return max(dfs(i, j) for i in range(m) for j in range(n))  # 枚举所有格子作为起点，取其中最大的收益
