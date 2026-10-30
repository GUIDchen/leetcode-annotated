# 4004. 使循环数组余额非负的最少移动次数 II / Minimum Moves to Balance Circular Array II（困难）
# 核心思路：每次操作把 1 单位余额转移给相邻的人，等价于沿环上的相邻边运输 1 单位、代价 1；于是建最小费用最大流——源点连正余额（容量=余额、费用 0），负余额连汇点（容量=缺口、费用 0），环上相邻两人之间连双向边（容量无穷、费用 1），把缺口总量送到汇点的最小费用就是最少操作次数。
# 复杂度：节点与边均为 O(n)；时间按增广轮数计（每轮 SPFA 在 O(n) 的环图上运行），空间 O(n)。
class Solution:  # 题解类
    def minMoves(self, balance: List[int]) -> int:  # 返回使每个人余额都非负所需的最少操作次数
        total_balance = sum(balance)  # 所有人余额之和
        if total_balance < 0:  # 总余额为负，怎么搬都补不平
            return -1  # 返回 -1 表示无法做到

        n = len(balance)  # 人数，也就是环长
        total_deficit = sum(-x for x in balance if x < 0)  # 缺口总量：所有负余额的绝对值之和
        if total_deficit == 0:  # 本来就没有缺口
            return 0  # 无需任何操作

        source = n  # 源点编号
        sink = n + 1  # 汇点编号
        num_nodes = n + 2  # 总节点数：n 个位置 + 源点 + 汇点

        graph = [[] for _ in range(num_nodes)]  # 邻接表，每条边存 [终点, 剩余容量, 单位费用, 反向边下标]

        def add_edge(u, v, cap, cost):  # 加入一条 u→v 的边以及它的反向边
            graph[u].append([v, cap, cost, len(graph[v])])  # 正向边，其反向边指向 v 当前边表末尾
            graph[v].append([u, 0, -cost, len(graph[u]) - 1])  # 反向边容量为 0、费用取负，指回刚加入的正向边

        for i in range(n):  # 为每个位置建边
            if balance[i] > 0:  # 有盈余的位置
                add_edge(source, i, balance[i], 0)  # 源点向它提供 balance[i] 单位流量，费用 0
            elif balance[i] < 0:  # 有缺口的位置
                add_edge(i, sink, -balance[i], 0)  # 它需要 -balance[i] 单位流量，费用 0

            add_edge(i, (i + 1) % n, inf, 1)  # 向右相邻转移 1 单位余额，代价 1
            add_edge(i, (i - 1 + n) % n, inf, 1)  # 向左相邻转移 1 单位余额，代价 1

        total_cost = 0  # 累计总费用
        current_flow = 0  # 已经送出的流量

        while current_flow < total_deficit:  # 每次沿当前残量网络的最短路增广，直到送满缺口
            dist = [inf] * num_nodes  # 本轮最短路距离
            parent_node = [-1] * num_nodes  # 最短路上的前驱节点
            parent_edge = [-1] * num_nodes  # 最短路上的前驱边下标
            in_queue = [False] * num_nodes  # 节点是否在队列中，SPFA 用

            queue = deque([source])  # SPFA 队列，源点先入队
            dist[source] = 0  # 源点距离为 0
            in_queue[source] = True  # 标记源点在队列中

            while queue:  # SPFA 求当前残量网络上的最短路
                u = queue.popleft()  # 取队首节点（此处未使用节点编号以外信息）
                in_queue[u] = False  # 清除入队标记

                for idx, (v, cap, cost, _) in enumerate(graph[u]):  # 枚举 u 的所有出边
                    if cap > 0 and dist[v] > dist[u] + cost:  # 仍有剩余容量且可以松弛
                        dist[v] = dist[u] + cost  # 更新最短距离
                        parent_node[v] = u  # 记录前驱节点
                        parent_edge[v] = idx  # 记录前驱边下标
                        if not in_queue[v]:  # 目标点不在队列中
                            queue.append(v)  # 入队继续松弛
                            in_queue[v] = True  # 标记入队

            if dist[sink] == inf:  # 汇点不可达，说明缺口无法补齐
                break  # 跳出增广循环

            push_flow = total_deficit - current_flow  # 本轮最多能增广的流量
            curr = sink  # 从汇点开始回溯
            while curr != source:  # 沿最短路回溯到源点
                p = parent_node[curr]  # 前驱节点
                idx = parent_edge[curr]  # 前驱边下标
                push_flow = min(push_flow, graph[p][idx][1])  # 可增广流量受路径上最小剩余容量限制
                curr = p  # 继续向上回溯

            curr = sink  # 再次从汇点开始回溯
            while curr != source:  # 沿路径实际修改流量
                p = parent_node[curr]  # 前驱节点
                idx = parent_edge[curr]  # 前驱边下标
                rev_idx = graph[p][idx][3]  # 反向边下标
                graph[p][idx][1] -= push_flow  # 正向边剩余容量减少
                graph[curr][rev_idx][1] += push_flow  # 反向边剩余容量增加
                curr = p  # 继续向上回溯

            current_flow += push_flow  # 累加已送出的流量
            total_cost += push_flow * dist[sink]  # 按单位最短路费用累计总费用

        return total_cost if current_flow == total_deficit else -1  # 缺口补齐则返回最小费用，否则返回 -1
