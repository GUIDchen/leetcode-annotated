# 题目：2039. 网络空闲的时刻（The Time When the Network Becomes Idle）
# 思路：从主服务器 0 出发做 BFS 求每个数据服务器的单程距离 d，往返 t = 2d；最后重发时刻为 (t-1)//patience*patience，空闲时刻是该时刻加 t 再加 1。
# 时间复杂度：O(n + m)，BFS 每条边只访问常数次；空间复杂度：O(n + m)，邻接表、队列与访问集合。
class Solution:  # LeetCode 约定的题解类
    def networkBecomesIdle(self, edges: List[List[int]], patience: List[int]) -> int:  # edges：无向边集合；patience：每个数据服务器的重发间隔
        g = defaultdict(list)  # 邻接表用 defaultdict，访问未出现的键会自动创建空列表
        for u, v in edges:  # 逐条边构建无向图
            g[u].append(v)  # u 的邻居中加入 v
            g[v].append(u)  # 反向也加一条，构成无向边
        q = deque([0])  # BFS 队列，起点是主服务器 0
        vis = {0}  # 集合记录已入队的节点，防止重复访问
        ans = d = 0  # ans：最终空闲时刻；d：当前层数，即单程距离
        while q:  # 队列非空就继续逐层扩展
            d += 1  # 进入下一层，单程距离加一
            t = d * 2  # 往返时间 t = 2d
            for _ in range(len(q)):  # 固定当前层节点数，只弹出这一层的节点
                u = q.popleft()  # 弹出队首节点
                for v in g[u]:  # 遍历 u 的所有邻居
                    if v not in vis:  # 只处理尚未访问的邻居
                        vis.add(v)  # 标记已访问，保证每个节点只入队一次
                        q.append(v)  # 邻居入队，留待下一层扩展
                        ans = max(ans, (t - 1) // patience[v] * patience[v] + t + 1)  # 最后一次重发时刻 (t-1)//patience[v]*patience[v]，加往返 t 与 1 秒即网络空闲时刻，对全部节点取最大
        return ans
