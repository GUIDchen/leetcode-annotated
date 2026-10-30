# 题目：3123. 最短路径中的边（Find Edges in Shortest Paths）
# 思路：先以 0 为源点跑 Dijkstra 求出到各点的最短路，再从终点 n-1 反向 BFS，把满足 dist[a] == dist[b] + w 的边标记为答案。
# 时间复杂度：O(m log n)，m 为边数、n 为点数；空间复杂度：O(n + m)。
class Solution:  # LeetCode 约定的题解类
    def findAnswer(self, n: int, edges: List[List[int]]) -> List[bool]:  # 返回长度为 m 的列表，标记每条边是否可能在某条 0 -> n-1 的最短路上
        g = defaultdict(list)  # 邻接表：结点 -> [(邻点, 边权, 边编号)]
        for i, (a, b, w) in enumerate(edges):  # 建无向图，同时保留每条边的编号 i
            g[a].append((b, w, i))  # a -> b 的记录，带上边编号 i
            g[b].append((a, w, i))  # b -> a 的反向记录
        dist = [inf] * n  # dist[x]：从 0 号点到 x 号点的最短距离
        dist[0] = 0  # 起点到自己的距离为 0
        q = [(0, 0)]  # 小根堆，元素为 (距离, 结点)
        while q:  # Dijkstra 主循环
            da, a = heappop(q)  # 取出距离最小的结点
            if da > dist[a]:  # 过期条目：该结点已有更短的路径
                continue  # 直接跳过
            for b, w, _ in g[a]:  # 松弛 a 的所有出边（边编号这里用不到）
                if dist[b] > dist[a] + w:  # 发现一条更短的路径
                    dist[b] = dist[a] + w  # 更新到 b 的最短距离
                    heappush(q, (dist[b], b))  # 把新距离入堆，供后续松弛
        m = len(edges)  # 边数
        ans = [False] * m  # 答案数组，默认全部为 False
        if dist[n - 1] == inf:  # 终点不可达，说明不存在任何最短路
            return ans  # 直接返回全 False
        q = deque([n - 1])  # 从终点出发反向 BFS
        while q:  # BFS 主循环
            a = q.popleft()  # 取出队首结点
            for b, w, i in g[a]:  # 枚举 a 的邻边（i 是边编号）
                if dist[a] == dist[b] + w:  # 反向走这条边距离不变，说明它位于最短路径上
                    ans[i] = True  # 标记这条边
                    q.append(b)  # 继续从 b 反向扩展
        return ans  # 返回标记结果
