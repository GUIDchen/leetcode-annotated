# 题目：1334. 阈值距离内邻居最少的城市（Find the City With the Smallest Number of Neighbors at a Threshold Distance）
# 思路：建立邻接矩阵后，对每个城市跑一次朴素 Dijkstra，统计距离不超过阈值的城市数；从大到小枚举城市并只在严格更小时更新，使并列时保留编号更大的城市。
# 时间复杂度：O(n^3)，n 次 O(n^2) 的 Dijkstra；空间复杂度：O(n^2)，存储邻接矩阵 g。
class Solution:  # LeetCode 约定的题解类
    def findTheCity(  # n 为城市数，edges 为 [u, v, w] 边表，distanceThreshold 为距离阈值
        self, n: int, edges: List[List[int]], distanceThreshold: int  # self 是实例本身；三个参数分别是城市数、边表、阈值
    ) -> int:  # 返回满足条件的城市编号
        def dijkstra(u: int) -> int:  # 内部函数：以 u 为源点跑 Dijkstra，返回距离不超过阈值的城市数（含自身）
            dist = [inf] * n  # 距离数组初始化为无穷大
            dist[u] = 0  # 源点到自身距离为 0
            vis = [False] * n  # 访问标记：该点最短路是否已确定
            for _ in range(n):  # 共 n 轮，每轮确定一个点的最短路
                k = -1  # 本轮要选出的、当前距离最小的未访问点
                for j in range(n):  # 在全部未访问点里挑距离最小的
                    if not vis[j] and (k == -1 or dist[k] > dist[j]):  # k == -1 表示还没有候选点，直接取；否则比距离
                        k = j  # 更新候选点
                vis[k] = True  # 标记 k 的最短路已确定
                for j in range(n):  # 用 k 作为中转松弛其它所有点
                    # dist[j] = min(dist[j], dist[k] + g[k][j])
                    if dist[k] + g[k][j] < dist[j]:  # 松弛：经由 k 走更短就更新 dist[j]
                        dist[j] = dist[k] + g[k][j]  # 更新为更短的距离
            return sum(d <= distanceThreshold for d in dist)  # 统计不超过阈值的城市数（含自身，对所有城市都多算 1，不影响比较）

        g = [[inf] * n for _ in range(n)]  # 邻接矩阵：不可达用 inf 表示
        for f, t, w in edges:  # 把边表写成邻接矩阵
            g[f][t] = g[t][f] = w  # 无向边，两个方向同时赋值
        ans, cnt = n, inf  # ans 记答案城市，cnt 记当前最少的邻居数
        for i in range(n - 1, -1, -1):  # 从大到小枚举，并列时保留编号更大的城市
            if (t := dijkstra(i)) < cnt:  # 海象运算符：先算出城市 i 的邻居数 t，再与当前最优比较
                cnt, ans = t, i  # 严格更小时才更新
        return ans  # 返回邻居最少且编号最大的城市
