# 题目：1976. 到达目的地的方案数（Number of Ways to Arrive at Destination）
# 思路：Dijkstra 求最短路，同时用 f 数组记录方案数：松弛出更短距离时覆盖，距离相等时累加，最后统一取模返回。
# 时间复杂度：O(n^2)，每轮线性找最小点；空间复杂度：O(n^2)，主要开销是邻接矩阵。
class Solution:  # LeetCode 约定的题解类
    def countPaths(self, n: int, roads: List[List[int]]) -> int:  # n 个节点，roads 中每条边形如 [u, v, t]，返回 0 到 n-1 的最短路条数
        g = [[inf] * n for _ in range(n)]  # 邻接矩阵：没有直接边的格子先填成正无穷 inf
        for u, v, t in roads:  # 逐条读入道路
            g[u][v] = g[v][u] = t  # 无向边，两个方向一起赋值
        g[0][0] = 0  # 起点到自身距离为 0，保证它第一个被定型
        dist = [inf] * n  # dist[i]：0 号点到 i 号点的最短路长度
        dist[0] = 0  # 起点距离为 0
        f = [0] * n  # f[i]：0 号点到 i 号点的最短路条数
        f[0] = 1  # 起点到自身算作 1 条（空的路径）
        vis = [False] * n  # vis[i]：i 号点的最短路是否已经确定
        for _ in range(n):  # 每轮定型一个点，共 n 轮
            t = -1  # t 存本轮 dist 最小的未定点，-1 表示尚未找到
            for j in range(n):  # 线性扫描所有点
                if not vis[j] and (t == -1 or dist[j] < dist[t]):  # 该点未定型，并且比当前候选更近
                    t = j  # 更新候选点
            vis[t] = True  # t 的最短路已经确定
            for j in range(n):  # 用 t 去松弛其余所有点
                if j == t:  # 自己松弛自己没有意义
                    continue  # 直接跳过
                ne = dist[t] + g[t][j]  # 经 t 中转到 j 的候选距离
                if dist[j] > ne:  # 候选距离更短，说明找到了更好的路
                    dist[j] = ne  # 更新最短距离
                    f[j] = f[t]  # 旧方案全部作废，直接继承 t 的方案数
                elif dist[j] == ne:  # 距离恰好相等，说明多出了一种同样短的走法
                    f[j] += f[t]  # 方案数累加（最后统一取模，避免每步取模的开销）
        mod = 10**9 + 7  # 题目要求的模数
        return f[-1] % mod  # 返回 0 到 n-1 的最短路条数（取模后返回）
