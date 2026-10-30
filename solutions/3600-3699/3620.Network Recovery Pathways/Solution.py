# 3620. Network Recovery Pathways（3620. 恢复网络路径）
# 核心思路：二分最终路径的“最小边权”mid，每次只保留权值 >= mid 的边，用 Dijkstra 求 0 到 n-1 的最短路并判断是否不超过 k，可行就抬高下界。
# 复杂度：二分 O(log W) 轮，每轮 Dijkstra O((n + m) log n)，总时间 O((n + m) log n log W)，空间 O(n + m)。
class Solution:  # 定义题解类
    def findMaxPathScore(  # 求在线路径分数最大值
        self, edges: List[List[int]], online: List[bool], k: int  # 边集、在线标记、预算 k
    ) -> int:  # 返回最大可行分数，不可达返回 -1
        def check(mid: int) -> int:  # 判定：只走权值 >= mid 的边，能否在预算 k 内到达终点
            dist = [inf] * n  # 最短路数组，初始化为无穷大
            dist[0] = 0  # 起点到自身距离为 0
            pq = [(0, 0)]  # 小顶堆，元素为 (距离, 顶点)
            while pq:  # 堆非空时继续扩展
                d, u = heappop(pq)  # 取出当前距离最小的状态
                if d > k:  # 累计花费已超预算
                    return False  # 不可行
                if u == n - 1:  # 已到终点且未超预算
                    return True  # 可行
                if dist[u] < d:  # 过期状态
                    continue  # 跳过
                for v, w in g[u]:  # 遍历 u 的所有出边
                    if w < mid:  # 边权小于 mid
                        continue  # 不允许经过
                    if dist[u] + w < dist[v]:  # 可以松弛
                        dist[v] = dist[u] + w  # 更新最短路
                        heappush(pq, (dist[v], v))  # 新状态入堆
            return False  # 无法在预算内到达终点

        n = len(online)  # 顶点个数
        g = [[] for _ in range(n)]  # 邻接表
        l, r = inf, 0  # 二分边界：可行边权的最小值与最大值
        for (  # 遍历所有边建图
            u,  # 边的起点
            v,  # 边的终点
            w,  # 边的权值
        ) in edges:  # 解包成 (u, v, w)
            if not online[u] or not online[v]:  # 任一端点离线
                continue  # 丢弃这条边
            g[u].append((v, w))  # 加入有向边 u -> v
            l = min(l, w)  # 更新下界
            r = max(r, w)  # 更新上界

        while l < r:  # 二分最短路边权的最大可行值
            mid = (l + r + 1) >> 1  # 取上中位数，与 l = mid 配合避免死循环
            if check(mid):  # mid 可行，答案不小于 mid
                l = mid  # 抬高下界
            else:  # mid 不可行，答案更小
                r = mid - 1  # 降低上界
        return l if check(l) else -1  # 再验证一次最终答案，不可达则返回 -1
