# 题目：1514. 概率最大的路径（Path with Maximum Probability）
# 思路：Dijkstra 变体：把概率相乘当路径代价，用最小堆（存负概率模拟大顶堆）按概率从大到小松弛。
# 时间复杂度：O((V+E) log V)；空间复杂度：O(V+E)，邻接表 + dist 数组 + 堆。
class Solution:  # LeetCode 约定的题解类
    def maxProbability(  # 方法签名：参数较多，按每行一个参数书写
        self,  # self：实例引用
        n: int,  # n：节点数
        edges: List[List[int]],  # edges：无向边列表，每个元素是 [a, b]
        succProb: List[float],  # succProb：与 edges 一一对应的边成功概率
        start_node: int,  # start_node：起点编号
        end_node: int,  # end_node：终点编号
    ) -> float:  # 返回从起点到终点的最大成功概率
        g: List[List[Tuple[int, float]]] = [[] for _ in range(n)]  # 邻接表：g[a] 存放 (邻居 b, 边概率 p)
        for (a, b), p in zip(edges, succProb):  # 同时遍历边与对应概率
            g[a].append((b, p))  # 正向边 a -> b
            g[b].append((a, p))  # 反向边 b -> a（无向图）
        pq = [(-1, start_node)]  # 堆中存 (-概率, 节点)，取负号让概率大的先弹出
        dist = [0] * n  # dist[v]：起点到 v 的最大概率，0 表示暂不可达
        dist[start_node] = 1  # 起点到自身概率为 1
        while pq:  # 堆非空说明还有可松弛的状态
            w, a = heappop(pq)  # 弹出当前概率最大的状态
            w = -w  # 还原成正的概率
            if dist[a] > w:  # 堆中的历史条目可能已过期（小于已知最优值）
                continue  # 过期条目直接跳过
            for b, p in g[a]:  # 枚举 a 的所有邻边
                if (t := w * p) > dist[b]:  # 海象运算符：先算出经过该边的新概率 t，再判断是否更优
                    dist[b] = t  # 松弛成功，更新到 b 的最大概率
                    heappush(pq, (-t, b))  # 把更优状态以负概率压入堆
        return dist[end_node]  # 返回终点的最大概率，不可达时为 0
