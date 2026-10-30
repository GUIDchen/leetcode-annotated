# 题目：2473. 购买苹果的最低成本（Minimum Cost to Buy Apples）
# 思路：把 roads 建成无向带权图，对每个城市作为买苹果的地点跑一次堆优化 Dijkstra；走到 u 买苹果总花费 = appleCost[u] + dist[u]*(k+1)，因为每走一条边自己要吃 k 个、路上还要吃 1 个，取最小值。
# 时间复杂度：O(n * m log m)，相当于做 n 次 Dijkstra；空间复杂度：O(n + m)，存邻接表与距离数组。
class Solution:  # LeetCode 约定的题解类
    def minCost(  # n 为城市数，roads 为无向道路，appleCost 为各地苹果单价，k 为每走一条路自吃的苹果数
        self, n: int, roads: List[List[int]], appleCost: List[int], k: int  # 续行写参数：n 为城市数，roads 为无向道路，appleCost 为单价，k 为每步自吃苹果数
    ) -> List[int]:  # 返回每个城市对应的最低成本
        def dijkstra(i):  # 以 i 为起点的单源最短路，返回买苹果的最优总花费
            q = [(0, i)]  # 小根堆，初始只有起点，到自身距离 0
            dist = [inf] * n  # 距离数组，先全部设为无穷大
            dist[i] = 0  # 起点到自身的距离确定为 0
            ans = inf  # 当前起点的最优花费
            while q:  # 堆非空就继续取距离最小的点扩展
                d, u = heappop(q)  # 弹出堆顶，取得最短距离与对应顶点
                ans = min(ans, appleCost[u] + d * (k + 1))  # 在 u 买苹果的总价：苹果单价 + 路上消耗的苹果数
                for v, w in g[u]:  # 遍历 u 的所有邻居
                    if dist[v] > dist[u] + w:  # 发现更短的路径才做松弛
                        dist[v] = dist[u] + w  # 更新 v 的最短距离
                        heappush(q, (dist[v], v))  # 把更新后的 v 重新入堆
            return ans  # 返回该起点的最小总花费

        g = defaultdict(list)  # 邻接表建图
        for a, b, c in roads:  # 逐条读入道路
            a, b = a - 1, b - 1  # 题目下标从 1 开始，这里统一转成从 0 开始
            g[a].append((b, c))  # a → b 的有向边
            g[b].append((a, c))  # b → a 的有向边，两条合起来构成无向图
        return [dijkstra(i) for i in range(n)]  # 每个城市都当一次买苹果的地点
