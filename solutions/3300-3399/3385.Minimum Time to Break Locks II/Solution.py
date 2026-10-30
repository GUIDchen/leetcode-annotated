# 题目：3385. 破解锁的最少时间 II（Minimum Time to Break Locks II）
# 思路：把「第 i 把锁安排在第 j+1 个位置破解」建成二分图的最小费用流，边权 ceil(a[i] / (j+1))，求满流 n 时的最小费用。
# 时间复杂度：O(n^3 log n) 量级（逐条增广 + 堆优化最短路）；空间复杂度：O(n^2)，二分图边数为 n^2。
class MCFGraph:  # 最小费用流（MCF）模板类
    class Edge(NamedTuple):  # 描述一条边的对外数据结构
        src: int  # 起点
        dst: int  # 终点
        cap: int  # 总容量
        flow: int  # 当前流量
        cost: int  # 单位费用

    class _Edge:  # 内部边结构，带指向反向边的引用
        def __init__(self, dst: int, cap: int, cost: int) -> None:  # 构造一条内部边
            self.dst = dst  # 记录终点
            self.cap = cap  # 记录剩余容量
            self.cost = cost  # 记录单位费用
            self.rev: Optional[MCFGraph._Edge] = None  # rev 指向反向边，稍后由 add_edge 互相绑定

    def __init__(self, n: int) -> None:  # 构造含 n 个点的费用流图
        self._n = n  # 顶点数
        self._g: List[List[MCFGraph._Edge]] = [[] for _ in range(n)]  # 邻接表：每个点保存自己的出边对象
        self._edges: List[MCFGraph._Edge] = []  # 额外保存正向边列表，便于按编号查询

    def add_edge(self, src: int, dst: int, cap: int, cost: int) -> int:  # 加一条容量 cap、单位费用 cost 的边 src -> dst，返回边编号
        assert 0 <= src < self._n  # 断言起点下标合法
        assert 0 <= dst < self._n  # 断言终点下标合法
        assert 0 <= cap  # 断言容量非负
        m = len(self._edges)  # 新边编号就是当前已有边的数量
        e = MCFGraph._Edge(dst, cap, cost)  # 建正向边
        re = MCFGraph._Edge(src, 0, -cost)  # 建反向边：容量 0、费用取负
        e.rev = re  # 正向边的 rev 指向反向边
        re.rev = e  # 反向边的 rev 指回正向边
        self._g[src].append(e)  # 正向边挂到 src 的邻接表
        self._g[dst].append(re)  # 反向边挂到 dst 的邻接表
        self._edges.append(e)  # 记录正向边
        return m  # 返回边编号

    def get_edge(self, i: int) -> Edge:  # 查询第 i 条边当前的状态
        assert 0 <= i < len(self._edges)  # 断言编号合法
        e = self._edges[i]  # 取出正向边
        re = cast(MCFGraph._Edge, e.rev)  # 取出它对应的反向边
        return MCFGraph.Edge(re.dst, e.dst, e.cap + re.cap, re.cap, e.cost)  # 总容量 = 剩余容量 + 已流量，用正反两条边拼出对外信息

    def edges(self) -> List[Edge]:  # 返回所有边的状态列表
        return [self.get_edge(i) for i in range(len(self._edges))]  # 逐条查询并组装

    def flow(self, s: int, t: int, flow_limit: Optional[int] = None) -> Tuple[int, int]:  # 求 s 到 t、流量上限 flow_limit 的最小费用流
        return self.slope(s, t, flow_limit)[-1]  # slope 的最后一段就是满流（或无法再增广）时的流量与费用

    def slope(  # 返回「流量-费用」的分段端点（斜率单调不减）
        self, s: int, t: int, flow_limit: Optional[int] = None  # 参数：起点、汇点、流量上限
    ) -> List[Tuple[int, int]]:  # 返回值：若干 (流量, 累计费用) 端点
        assert 0 <= s < self._n  # 断言起点下标合法
        assert 0 <= t < self._n  # 断言汇点下标合法
        assert s != t  # 起点与汇点不能相同
        if flow_limit is None:  # 没有指定流量上限
            flow_limit = cast(int, sum(e.cap for e in self._g[s]))  # 默认上限取源点所有出边的容量之和

        dual = [0] * self._n  # dual：每个点的势能，保证修正后的边权非负
        prev: List[Optional[Tuple[int, MCFGraph._Edge]]] = [None] * self._n  # prev[w] 记录最短路树上 w 的前驱点与所用的边

        def refine_dual() -> bool:  # 用当前势能跑一次 Dijkstra，成功则更新势能并返回 True
            pq = [(0, s)]  # 小根堆，初始只有起点（距离 0）
            visited = [False] * self._n  # 标记点是否已确定最短路
            dist: List[Optional[int]] = [None] * self._n  # dist[v] 为 None 表示还没被松弛到
            dist[s] = 0  # 起点距离为 0
            while pq:  # 堆非空就继续松弛
                dist_v, v = heappop(pq)  # 弹出当前距离最小的点
                if visited[v]:  # 该点已经确定过最短路
                    continue  # 跳过过期堆条目
                visited[v] = True  # 标记为已确定
                if v == t:  # 到达汇点即可提前结束
                    break  # 跳出循环
                dual_v = dual[v]  # 当前点的势能
                for e in self._g[v]:  # 遍历它的所有出边
                    w = e.dst  # 边指向的邻居
                    if visited[w] or e.cap == 0:  # 邻居已确定最短路，或边没有剩余容量
                        continue  # 跳过这条不可用的边
                    reduced_cost = e.cost - dual[w] + dual_v  # 修正后的边权：cost + dual[v] - dual[w]（非负）
                    new_dist = dist_v + reduced_cost  # 经过这条边后的新距离
                    dist_w = dist[w]  # 邻居当前的最短距离
                    if dist_w is None or new_dist < dist_w:  # 第一次到达，或新距离更短
                        dist[w] = new_dist  # 更新距离
                        prev[w] = v, e  # 记录前驱点与边
                        heappush(pq, (new_dist, w))  # 入堆等待继续松弛
            else:  # while 因堆空而正常结束才会走到 else
                return False  # 说明汇点不可达，没有增广路
            dist_t = dist[t]  # 汇点的最短路距离
            for v in range(self._n):  # 用本次距离更新所有已确定点的势能
                if visited[v]:  # 只更新被访问过的点
                    dual[v] -= cast(int, dist_t) - cast(int, dist[v])  # 势能下调 dist_t - dist[v]
            return True  # 成功找到一条增广路

        flow = 0  # 当前累计流量
        cost = 0  # 当前累计费用
        prev_cost_per_flow: Optional[int] = None  # 上一段的单位费用，用于合并同斜率的段
        result = [(flow, cost)]  # 结果从 (0, 0) 开始
        while flow < flow_limit:  # 流量未到上限就继续增广
            if not refine_dual():  # 先更新势能并求最短路
                break  # 没有增广路就结束
            f = flow_limit - flow  # 本次最多能增广的流量
            v = t  # 从汇点开始沿最短路回溯
            while prev[v] is not None:  # 回溯到起点之前停止
                u, e = cast(Tuple[int, MCFGraph._Edge], prev[v])  # 取出前驱点与边
                f = min(f, e.cap)  # 取路径上的瓶颈容量
                v = u  # 继续往前回溯
            v = t  # 重新从汇点开始，第二趟真正修改容量
            while prev[v] is not None:  # 同样回溯到起点为止
                u, e = cast(Tuple[int, MCFGraph._Edge], prev[v])  # 取出前驱点与边
                e.cap -= f  # 正向边剩余容量减少
                assert e.rev is not None  # 断言反向边已绑定
                e.rev.cap += f  # 反向边容量增加，允许之后退流
                v = u  # 继续回溯
            c = -dual[s]  # 本段的单位费用
            flow += f  # 累加流量
            cost += f * c  # 累加费用
            if c == prev_cost_per_flow:  # 斜率与上一段相同
                result.pop()  # 合并：删掉上一段的端点
            result.append((flow, cost))  # 记录本段端点
            prev_cost_per_flow = c  # 记住本段单位费用
        return result  # 返回所有分段端点


class Solution:  # LeetCode 约定的题解类
    def findMinimumTime(self, a: List[int]) -> int:  # a：每把锁的强度值，返回破解全部锁的最少总时间
        n = len(a)  # 锁的数量
        s = n * 2  # 左部 n 个点代表锁，源点编号为 2n
        t = s + 1  # 汇点编号为 2n + 1
        g = MCFGraph(t + 1)  # 建图：一共 2n + 2 个点

        for i in range(n):  # 枚举每把锁
            g.add_edge(s, i, 1, 0)  # 源点 -> 锁 i：容量 1、费用 0
            g.add_edge(i + n, t, 1, 0)  # 位置 (i + n) -> 汇点：容量 1、费用 0
            for j in range(n):  # 枚举它被安排成第 j+1 个被破解
                g.add_edge(i, j + n, 1, (a[i] - 1) // (j + 1) + 1)  # 匹配费用为 ceil(a[i] / (j+1))，用整除写法避免浮点误差

        return g.flow(s, t, n)[1]  # 满流 n 的第二个分量就是最小总费用
