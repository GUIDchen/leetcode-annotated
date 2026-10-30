# 3778. 排除一个最大权重边的最小距离 / Minimum Distance Excluding One Maximum Weighted Edge
# 核心思路：把“可以免掉一条边的权重”建成第二维状态，在 (节点, 是否已用免费边) 的图上跑 Dijkstra，到达终点且已用掉免费边的距离即为答案。
# 复杂度：时间复杂度 O(m log n)，空间复杂度 O(n)，其中 n 为节点数，m 为边数。
class Solution:  # 定义题解类
    def minCostExcludingMax(self, n: int, edges: List[List[int]]) -> int:  # 返回从 0 到 n-1 且免费经过一条边的最短距离
        g = [[] for _ in range(n)]  # 邻接表：g[u] 保存 (相邻点, 边权)
        for u, v, w in edges:  # 逐条边建立无向图
            g[u].append((v, w))  # 加入 u -> v
            g[v].append((u, w))  # 加入 v -> u
        dist = [[inf] * 2 for _ in range(n)]  # dist[u][used]：到达 u 时是否已用掉“免费边”的最短路
        dist[0][0] = 0  # 起点 0，尚未使用免费边
        pq = [(0, 0, 0)]  # 小根堆，元素为 (距离, 节点, 是否已用免费边)
        while pq:  # Dijkstra 主循环
            cur, u, used = heappop(pq)  # 取出当前距离最小的状态
            if cur > dist[u][used]:  # 该状态已被更优解取代
                continue  # 直接跳过
            if u == n - 1 and used:  # 到达终点且已用掉免费边
                return cur  # 当前距离即为答案
            for v, w in g[u]:  # 遍历当前节点的所有相邻边
                nxt = cur + w  # 正常支付这条边的代价
                if nxt < dist[v][used]:  # 可以松弛就更新
                    dist[v][used] = nxt  # 更新最短路
                    heappush(pq, (nxt, v, used))  # 新状态入堆
                if used == 0:  # 还没用过免费边
                    nxt = cur  # 把这条边当作最大权重边免掉
                    if nxt < dist[v][1]:  # 可以松弛就更新
                        dist[v][1] = nxt  # 更新用掉免费边后的最短路
                        heappush(pq, (nxt, v, 1))  # 新状态入堆
        return dist[n - 1][1]  # 返回终点的答案
