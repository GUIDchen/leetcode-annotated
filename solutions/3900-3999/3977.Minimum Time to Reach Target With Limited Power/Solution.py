# 3977. Minimum Time to Reach Target With Limited Power | 有限电量到达目标节点的最少时间（困难）
# 核心思路：把状态定义为（节点, 剩余电量），在这个扩展图上跑 Dijkstra 求最短路；堆里按（时间, 剩余电量的相反数）排序，于是时间相同时电量更多的状态先出队，第一次弹出 target 时得到的时间与电量即答案，走不到则返回 [-1, -1]。
# 复杂度：时间 O((n + m) · power · log(n · power))，m 为边数；空间 O(n · power)，主要是 dist 表与堆。
class Solution:  # 定义题解类
    def minTimeMaxPower(  # 返回 [最少时间, 该时间下剩余电量]，不可达时返回 [-1, -1]
        self,  # 绑定实例
        n: int,  # 节点个数
        edges: List[List[int]],  # 有向边列表，每条边是 [u, v, t]
        power: int,  # 出发时的总电量
        cost: List[int],  # cost[u]：离开节点 u 需要消耗的电量
        source: int,  # 起点
        target: int,  # 终点
    ) -> List[int]:  # 返回值为长度为 2 的列表
        g = [[] for _ in range(n)]  # 邻接表，g[u] 里存 (后继节点, 边耗时)
        for u, v, t in edges:  # 遍历每条有向边
            g[u].append((v, t))  # 只建单向边，题目给的是有向图
        dist = [[inf] * (power + 1) for _ in range(n)]  # dist[u][p]：到达 u 且剩余 p 电量时的最少时间
        dist[source][power] = 0  # 起点：满电，时间 0
        pq = [(0, -power, source)]  # 小根堆；电量取负，使时间相同时电量多者排在前面
        while pq:  # 标准 Dijkstra 主循环
            d, p, u = heappop(pq)  # 取出当前最优状态：时间 d、电量编码 p、节点 u
            p = -p  # 把负号还原成真实的剩余电量
            if u == target:  # 第一次弹出终点即为最优：时间最少，且时间相同时电量最多
                return [d, p]  # 直接返回 {时间, 剩余电量}
            if d > dist[u][p] or p < cost[u]:  # 懒删除过期状态；电量不足以离开 u 时该状态无法继续扩展
                continue  # 丢弃这个状态
            p -= cost[u]  # 离开 u 要付出代价：先扣掉 cost[u]，剩下的电量才能带到后继节点
            for v, t in g[u]:  # 枚举从 u 出发的每条边
                nd = d + t  # 走到 v 之后的总时间
                if nd < dist[v][p]:  # 用扣掉电量后的剩余 p 作为新状态，发现更短时间
                    dist[v][p] = nd  # 更新该状态的最短时间
                    heappush(pq, (nd, -p, v))  # 新状态入堆，电量同样取负
        return [-1, -1]  # 堆空仍未弹出 target，说明在电量限制下不可达
