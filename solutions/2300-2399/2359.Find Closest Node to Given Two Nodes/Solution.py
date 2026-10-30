# 题目：2359. 找到离给定两个节点最近的节点（Find Closest Node to Given Two Nodes）
# 思路：每个点出度至多为 1，从两个起点各做一次 BFS 求距离，再选 max(d1[i], d2[i]) 最小的 i。
# 时间复杂度：O(n)，两次 BFS 各遍历一遍点与边；空间复杂度：O(n)，邻接表与两个距离数组。
class Solution:  # LeetCode 约定的题解类
    def closestMeetingNode(self, edges: List[int], node1: int, node2: int) -> int:  # edges：每个点唯一的出边，-1 表示没有出边；返回答案节点下标
        def f(i):  # 内层函数：从起点 i 出发，BFS 求出到每个点的最短距离
            dist = [inf] * n  # 距离数组，初始全部视为不可达
            dist[i] = 0  # 起点到自己的距离为 0
            q = deque([i])  # 队列用起点初始化
            while q:  # 队列不空就继续扩展
                i = q.popleft()  # 弹出队首节点
                for j in g[i]:  # 遍历当前节点的所有出边
                    if dist[j] == inf:  # 目标点还没被访问过
                        dist[j] = dist[i] + 1  # BFS 首次到达即最短距离
                        q.append(j)  # 入队，等待继续向外扩展
            return dist  # 返回从起点 i 出发到所有点的距离数组

        g = defaultdict(list)  # 邻接表：g[i] 存放从 i 出发能到达的点
        for i, j in enumerate(edges):  # 遍历每条边，i 为起点、j 为终点
            if j != -1:  # 该点存在出边时才建边
                g[i].append(j)  # 把唯一的出边加入邻接表
        n = len(edges)  # n 为节点总数
        d1 = f(node1)  # node1 到每个点的最短距离
        d2 = f(node2)  # node2 到每个点的最短距离
        ans, d = -1, inf  # ans 记录答案节点，d 记录当前最小的“较大距离”
        for i, (a, b) in enumerate(zip(d1, d2)):  # 按下标从小到大扫描，天然满足“距离相同取下标最小”
            if (t := max(a, b)) < d:  # 海象运算符：先算出该点到两个起点的较大距离 t，再与 d 比较
                d = t  # 更新当前最优的较大距离
                ans = i  # 记录取得该最优值的节点
        return ans  # 没有两个起点都可到达的点时 ans 保持 -1
