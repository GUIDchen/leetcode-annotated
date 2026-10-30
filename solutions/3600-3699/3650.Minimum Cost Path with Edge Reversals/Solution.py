# 3650. 边反转的最小路径总成本（Minimum Cost Path with Edge Reversals）
# 核心思路：把 u -> v 花费 w 的有向边补一条 v -> u 花费 2w 的反向边，转成有向正权图后用 Dijkstra 求 0 到 n-1 的最短路。
# 复杂度：时间 O((n + m) log n)，空间 O(n + m)，其中 m 为边数。
class Solution:  # 定义题解类
    def minCost(self, n: int, edges: List[List[int]]) -> int:  # 返回 0 到 n-1 的最小总成本；edges 中每条 [u, v, w] 表示 u -> v 花费 w
        g = [[] for _ in range(n)]  # 邻接表：g[x] 保存从 x 出发的 (邻居, 边权)
        for u, v, w in edges:  # 遍历每条有向边
            g[u].append((v, w))  # 正常方向：u -> v 花费 w
            g[v].append((u, w * 2))  # 反转方向：v -> u 花费 2w（在 v 使用一次开关反向穿过）
        pq = [(0, 0)]  # 堆中元素为 (距离, 节点)，先把起点入堆
        dist = [inf] * n  # dist[i] 表示 0 到 i 的当前最短距离，初始为无穷大
        dist[0] = 0  # 起点走到自己距离为 0
        while pq:  # Dijkstra 主循环：堆不空就还有可松弛的状态
            d, u = heappop(pq)  # 弹出当前距离最小的状态
            if d > dist[u]:  # 距离已过期（已被更优值取代）
                continue  # 跳过这条失效记录
            if u == n - 1:  # 终点第一次出堆即得到最短距离
                return d  # 直接返回该距离
            for v, w in g[u]:  # 松弛 u 的所有出边
                nd = d + w  # 经过 u 到 v 的候选距离
                if nd < dist[v]:  # 候选距离更优时更新
                    dist[v] = nd  # 更新 v 的最短距离
                    heappush(pq, (nd, v))  # 新状态入堆
        return -1  # 无法到达终点时返回 -1
