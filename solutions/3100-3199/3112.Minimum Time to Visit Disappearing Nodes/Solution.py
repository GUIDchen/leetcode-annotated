# 题目：3112. 访问消失节点的最少时间（Minimum Time to Visit Disappearing Nodes）
# 思路：堆优化 Dijkstra 求最短路，松弛时额外判断「到达时间 < 该节点的消失时间」，保证不会经由已消失的点继续扩展。
# 时间复杂度：O((n + m) log n)，m 为边数；空间复杂度：O(n + m)，邻接表与距离数组的开销。
class Solution:  # LeetCode 约定的题解类
    def minimumTime(  # 求从节点 0 出发到每个节点的最少访问时间，n 是节点数
        self, n: int, edges: List[List[int]], disappear: List[int]  # edges 是无向边表，disappear 是各点的消失时间
    ) -> List[int]:  # 返回值：每个节点的最短到达时间，无法在消失前到达的为 -1
        g = defaultdict(list)  # 邻接表：g[u] 中存放 (邻点 v, 边权 w)
        for u, v, w in edges:  # 把边表展开成无向图
            g[u].append((v, w))  # 存正向边
            g[v].append((u, w))  # 存反向边，因为图是无向的
        dist = [inf] * n  # 距离数组初始化为无穷大
        dist[0] = 0  # 起点 0 到自身的距离为 0
        pq = [(0, 0)]  # 小根堆，元素为 (距离, 节点编号)，起点先入堆
        while pq:  # 堆空说明所有可达点都已完成松弛
            du, u = heappop(pq)  # 弹出当前距离最小的候选
            if du > dist[u]:  # 这是被更优值覆盖过的过期状态
                continue  # 直接跳过，避免重复扩展
            for v, w in g[u]:  # 枚举 u 的所有邻边
                if dist[v] > dist[u] + w and dist[u] + w < disappear[v]:  # 能走得更短，且到达时 v 还没有消失
                    dist[v] = dist[u] + w  # 更新 v 的最短距离
                    heappush(pq, (dist[v], v))  # 把新的候选距离入堆，供后续松弛
        return [a if a < b else -1 for a, b in zip(dist, disappear)]  # 在消失前能到达就取距离，否则记为 -1
