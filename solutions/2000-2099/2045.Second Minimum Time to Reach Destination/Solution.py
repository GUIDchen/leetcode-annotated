# 题目：2045. 到达目的地的第二短时间（Second Minimum Time to Reach Destination）
# 思路：先用 BFS 求出 1 号到每个点的最短与「严格第二短」步数（每个点记两个距离），再按跳数逐段累加时间，遇到红灯就把出发时刻推迟到下一个绿灯。
# 时间复杂度：O(V + E)，每个点最多入队两次；空间复杂度：O(V + E)，邻接表与距离数组。
class Solution:  # LeetCode 约定的题解类
    def secondMinimum(  # n 个节点，edges 是无向边，time 是经过一条边的耗时，change 是信号灯每段的时长
        self, n: int, edges: List[List[int]], time: int, change: int  # 参数依次是：节点数、无向边、每条边耗时、信号灯红/绿各持续的时间
    ) -> int:  # 返回从 1 号到 n 号的第二短时间
        g = defaultdict(set)  # 邻接表：g[u] 保存 u 的所有邻居，用 set 顺带去掉重复边
        for u, v in edges:  # 遍历每条无向边
            g[u].add(v)  # 建立 u 到 v 的邻接关系
            g[v].add(u)  # 建立 v 到 u 的邻接关系，无向图要双向加
        q = deque([(1, 0)])  # BFS 队列，元素是 (节点, 从 1 号出发走了几跳)
        dist = [[inf] * 2 for _ in range(n + 1)]  # dist[v][0] 存最短跳数，dist[v][1] 存严格第二短跳数，都先初始化为无穷大
        dist[1][1] = 0  # 起点 1 号把「第二短」这一位先设为 0，使后面任何一次到达都成为候选而非最短
        while q:  # 队列非空就继续扩展
            u, d = q.popleft()  # 取出队首节点和它对应的跳数
            for v in g[u]:  # 枚举这个节点的所有邻居
                if d + 1 < dist[v][0]:  # 找到了更短的走法：d+1 严格小于已知最短跳数
                    dist[v][0] = d + 1  # 更新最短跳数
                    q.append((v, d + 1))  # 把新状态入队，继续往后松弛
                elif dist[v][0] < d + 1 < dist[v][1]:  # 既不是最短、又严格小于已知第二短：这是一个合法的第二短候选
                    dist[v][1] = d + 1  # 更新第二短跳数
                    if v == n:  # 已经确定了终点的第二短跳数，不必再扩展
                        break  # 跳出邻居循环（只跳出 for，不跳出 while）
                    q.append((v, d + 1))  # 把这个第二短状态入队，用来继续发现更长的候选
        ans = 0  # 开始按跳数逐段累加真实时间
        for i in range(dist[n][1]):  # 终点需要走 dist[n][1] 跳，逐跳模拟
            ans += time  # 每走一跳先花掉 time 秒
            if i < dist[n][1] - 1 and (ans // change) % 2 == 1:  # 不是最后一跳时还要看红灯：ans // change 为奇数说明此刻处于红灯时段
                ans = (ans + change) // change * change  # 处于红灯就等到下一个绿灯开始，即把时间向上取整到 change 的整数倍
        return ans  # 返回到达终点 n 所需的第二短时间
