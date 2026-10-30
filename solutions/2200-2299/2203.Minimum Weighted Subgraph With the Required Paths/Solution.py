# 题目：2203. 包含要求路径的最小带权子图（Minimum Weighted Subgraph With the Required Paths）
# 思路：最优子图一定形如 src1→汇合点 + src2→汇合点 + 汇合点→dest，因此从 src1、src2 各跑一次正向 Dijkstra，再从 dest 在反图上跑一次，逐点求和取最小。
# 时间复杂度：O((n + m) log n)，三次 Dijkstra；空间复杂度：O(n + m)，正向图与反向图的邻接表。
class Solution:  # LeetCode 约定的题解类
    def minimumWeight(  # n：节点数；edges：有向边 [from, to, weight]；src1、src2：两个起点；dest：终点
        self, n: int, edges: List[List[int]], src1: int, src2: int, dest: int  # 参数列表续行：n 为节点数，src1、src2 为两个起点，dest 为终点
    ) -> int:  # 返回最小带权子图的总权值
        def dijkstra(g, u):  # 内部函数：从起点 u 出发求单源最短路（Dijkstra + 堆优化）
            dist = [inf] * n  # 距离数组：初始全为无穷大，表示尚未到达
            dist[u] = 0  # 起点到自身的距离为 0
            q = [(0, u)]  # 小根堆（优先队列），元素是 (当前距离, 节点编号)
            while q:  # 堆非空就一直取出当前距离最小的节点扩展
                d, u = heappop(q)  # 弹出堆顶：d 是距离，u 是节点（这里的 u 会遮蔽形参，形参已不再需要）
                if d > dist[u]:  # 堆里可能残留过期的旧记录，距离偏大就丢弃
                    continue  # 跳过过期记录，继续取下一个堆顶
                for v, w in g[u]:  # 遍历 u 的所有出边：v 是邻点，w 是边权
                    if dist[v] > dist[u] + w:  # 用 u 松弛 v：经 u 到达 v 更短才更新
                        dist[v] = dist[u] + w  # 更新 v 的最短距离
                        heappush(q, (dist[v], v))  # 把新的 (距离, 节点) 入堆，等待后续扩展
            return dist  # 返回从 u 出发到每个节点的最短距离

        g = defaultdict(list)  # 正向图邻接表：g[u] 存 (v, w)
        rg = defaultdict(list)  # 反向图邻接表：rg[v] 存 (u, w)，用于求「到 dest」的最短路
        for f, t, w in edges:  # 逐条读入有向边 (from, to, weight)
            g[f].append((t, w))  # 正向图加边 f → t，权值为 w
            rg[t].append((f, w))  # 反向图加边 t → f，权值不变：在反图上从 dest 出发就等于求各点到 dest 的距离
        d1 = dijkstra(g, src1)  # src1 到各节点的最短路
        d2 = dijkstra(g, src2)  # src2 到各节点的最短路
        d3 = dijkstra(rg, dest)  # 反图上从 dest 出发得到的最短路，即各节点到 dest 的最短路
        ans = min(sum(v) for v in zip(d1, d2, d3))  # 枚举汇合点：把三段距离逐点相加，zip 负责把三个数组按同一节点配对，取最小和
        return -1 if ans >= inf else ans  # 若最小和仍是无穷大说明要求的路径不存在，按题目要求返回 -1
