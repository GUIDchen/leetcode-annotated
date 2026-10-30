# 题目：2714. 找到 K 次跨越的最短路径（Find Shortest Path with K Hops）
# 思路：状态取 (节点, 已用跨越次数)，在分层图上跑 Dijkstra；普通边走权 w，跨越边花 0 但次数 +1。
# 时间复杂度：O(k(n+m) log(kn))，共 n(k+1) 个状态；空间复杂度：O(nk+m)，dist 表与邻接表。
class Solution:  # LeetCode 约定的题解类
    def shortestPathWithHops(  # 参数说明：n 节点数、edges 无向带权边、s 起点、d 终点、k 最多跨越次数
        self, n: int, edges: List[List[int]], s: int, d: int, k: int  # 参数续行：与上一行共同构成完整形参列表
    ) -> int:  # 返回最少花费；跨越多行书写只为控制行宽
        g = [[] for _ in range(n)]  # 邻接表：g[u] 存放 (相邻点, 边权)
        for u, v, w in edges:  # 逐条读入无向边
            g[u].append((v, w))  # 正向建边 u -> v
            g[v].append((u, w))  # 反向建边 v -> u
        dist = [[inf] * (k + 1) for _ in range(n)]  # dist[v][t]：到 v 且恰好用了 t 次跨越的最小花费，初值无穷大
        dist[s][0] = 0  # 起点的零次跨越状态花费为 0
        pq = [(0, s, 0)]  # 小根堆，元素为 (花费, 节点, 已用跨越次数)
        while pq:  # 堆非空就继续松弛
            dis, u, t = heappop(pq)  # 弹出当前花费最小的状态
            for v, w in g[u]:  # 枚举 u 的所有出边
                if t + 1 <= k and dist[v][t + 1] > dis:  # 用一次跨越直接到 v：不花边权，只把次数 +1，且不能超过 k
                    dist[v][t + 1] = dis  # 用零花费更新「跨越后」的状态
                    heappush(pq, (dis, v, t + 1))  # 新状态入堆，供后续继续扩展
                if dist[v][t] > dis + w:  # 不跨越，正常走这条边，花费加上边权 w
                    dist[v][t] = dis + w  # 更新「不跨越」状态的最小花费
                    heappush(pq, (dis + w, v, t))  # 新状态入堆
        return int(min(dist[d]))  # 终点 d 在所有跨越次数里的最小值就是答案，转成 int 输出
