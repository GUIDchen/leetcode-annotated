# 3651. 带传送的最小路径成本（Minimum Cost Path with Teleportations）
# 核心思路：f[t][i][j] 表示至多用 t 次传送到达 (i,j) 的最小成本；传送免费但要求目标格子的值不大于出发格子的值，故按格子值从大到小维护 f[t-1] 的前缀最小值即可完成一次传送，再对每层做一次向右/向下的网格 DP。
# 复杂度：时间 O(k·m·n + m·n·log(m·n))，空间 O(k·m·n)，其中 m、n 为矩阵行列数。
class Solution:  # 定义题解类
    def minCost(self, grid: List[List[int]], k: int) -> int:  # 返回从 (0,0) 到 (m-1,n-1) 的最小总成本，最多可免费传送 k 次
        m, n = len(grid), len(grid[0])  # 矩阵的行数与列数
        f = [[[inf] * n for _ in range(m)] for _ in range(k + 1)]  # f[t][i][j]：至多使用 t 次传送到达 (i,j) 的最小成本
        f[0][0][0] = 0  # 不使用传送时，起点成本为 0
        for i in range(m):  # 第一遍：只允许向右、向下走，做一次网格前缀 DP
            for j in range(n):  # 枚举列
                if i:  # 能从上方走来
                    f[0][i][j] = min(f[0][i][j], f[0][i - 1][j] + grid[i][j])  # 由上方格子的成本加上当前格子的值转移
                if j:  # 能从左方走来
                    f[0][i][j] = min(f[0][i][j], f[0][i][j - 1] + grid[i][j])  # 由左方格子的成本加上当前格子的值转移
        g = defaultdict(list)  # 按格子的值分组：g[x] 保存所有值等于 x 的格子坐标
        for i, row in enumerate(grid):  # 枚举行，同时拿到该行数据
            for j, x in enumerate(row):  # 枚举列，同时拿到格子值 x
                g[x].append((i, j))  # 把 (i, j) 加入值 x 对应的分组
        keys = sorted(g, reverse=True)  # 把所有出现过的值按从大到小排序
        for t in range(1, k + 1):  # 枚举传送次数，从 1 次到 k 次
            mn = inf  # mn 记录「值不小于当前处理值」的格子中 f[t-1] 的最小值
            for key in keys:  # 按值从大到小遍历分组
                pos = g[key]  # 取出当前值对应的所有格子坐标
                for i, j in pos:  # 先枚举当前值这一组的格子
                    mn = min(mn, f[t - 1][i][j])  # 把它们的 f[t-1] 也并入前缀最小值
                for i, j in pos:  # 再枚举当前值这一组的格子
                    f[t][i][j] = mn  # 传送本身免费，所以成本就是前缀最小值
            for i in range(m):  # 传送之后继续允许向右、向下走，再做一次网格 DP 松弛
                for j in range(n):  # 枚举列
                    if i:  # 能从上方走来
                        f[t][i][j] = min(f[t][i][j], f[t][i - 1][j] + grid[i][j])  # 由上方格子的成本加上当前格子的值转移
                    if j:  # 能从左方走来
                        f[t][i][j] = min(f[t][i][j], f[t][i][j - 1] + grid[i][j])  # 由左方格子的成本加上当前格子的值转移
        return min(f[t][m - 1][n - 1] for t in range(k + 1))  # 枚举实际使用的传送次数，返回到达终点的最小成本
