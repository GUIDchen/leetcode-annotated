# 题目：882. 细分图中的可到达节点（Reachable Nodes In Subdivided Graph）
# 思路：把每条边拆成 cnt+1 段后跑 Dijkstra，求出到每个原图节点的最少步数；原图节点按 maxMoves 统计，每条边内部再用两端剩余步数分段计算。
# 时间复杂度：O((n + m) log n)，堆优化 Dijkstra；空间复杂度：O(n + m)，邻接表与距离表。
class Solution:  # LeetCode 约定的题解类
    def reachableNodes(self, edges: List[List[int]], maxMoves: int, n: int) -> int:  # edges：{u, v, cnt}；maxMoves：最大步数；n：原图节点数
        g = defaultdict(list)  # 邻接表；每条边相邻两节点之间实际要走 cnt+1 步
        for u, v, cnt in edges:  # 逐条边建图
            g[u].append((v, cnt + 1))  # u→v 的边，权值为实际步数
            g[v].append((u, cnt + 1))  # v→u 的反向边，权值相同（无向图）
        q = [(0, 0)]  # 小根堆，元素是（距离, 节点），起点距离为 0
        dist = [0] + [inf] * n  # 距离表：起点 0 的距离为 0，其余先设为正无穷
        while q:  # Dijkstra 主循环
            d, u = heappop(q)  # 取出当前距离最小的节点
            for v, cnt in g[u]:  # 松弛 u 的所有邻居
                if (t := d + cnt) < dist[v]:  # 海象运算符：先算出新距离 t，再与已知距离比较
                    dist[v] = t  # 更新最短距离
                    heappush(q, (t, v))  # 新距离入堆，等待继续扩展
        ans = sum(d <= maxMoves for d in dist)  # 步数不超过 maxMoves 的原图节点都算到达
        for u, v, cnt in edges:  # 再统计每条边内部能到达的细分节点
            a = min(cnt, max(0, maxMoves - dist[u]))  # 从 u 侧出发还能深入多少个细分节点
            b = min(cnt, max(0, maxMoves - dist[v]))  # 从 v 侧出发还能深入多少个细分节点
            ans += min(cnt, a + b)  # 两侧合计不能超过这条边的细分节点总数
        return ans  # 返回可到达节点总数
