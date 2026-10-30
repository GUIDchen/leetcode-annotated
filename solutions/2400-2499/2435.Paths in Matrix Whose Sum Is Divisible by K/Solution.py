# 题目：2435. 矩阵中和能被 K 整除的路径（Paths in Matrix Whose Sum Is Divisible by K）
# 思路：三维 DP，f[i][j][k] 表示从左上角走到 (i,j) 且路径和模 K 余 k 的方案数；转移时由上方和左方按余数回推。
# 时间复杂度：O(m*n*K)，每个格子枚举 K 种余数；空间复杂度：O(m*n*K)，存下整张三维 DP 表。
class Solution:  # LeetCode 约定的题解类
    def numberOfPaths(self, grid: List[List[int]], K: int) -> int:  # grid：矩阵；K：要求整除的模数
        mod = 10**9 + 7  # 方案数可能很大，按题目要求对 1e9+7 取模
        m, n = len(grid), len(grid[0])  # m：行数；n：列数
        f = [[[0] * K for _ in range(n)] for _ in range(m)]  # 三维 DP 表，第三维长度 K，初值全为 0
        f[0][0][grid[0][0] % K] = 1  # 起点只有一条路径，其和的余数就是起点值模 K
        for i in range(m):  # 从上到下枚举每一行
            for j in range(n):  # 从左到右枚举每一列
                for k in range(K):  # 枚举走到 (i,j) 之后路径和模 K 的余数
                    k0 = ((k - grid[i][j] % K) + K) % K  # 回推：走到 (i,j) 之前的余数，加上当前格后正好变成 k
                    if i:  # 可以从上方 (i-1,j) 走下来
                        f[i][j][k] += f[i - 1][j][k0]  # 累加上方的方案数
                    if j:  # 可以从左方 (i,j-1) 走过来
                        f[i][j][k] += f[i][j - 1][k0]  # 累加左方的方案数
                    f[i][j][k] %= mod  # 统一取模，防止方案数溢出
        return f[m - 1][n - 1][0]  # 终点处余数为 0 的方案数就是能被 K 整除的路径条数
