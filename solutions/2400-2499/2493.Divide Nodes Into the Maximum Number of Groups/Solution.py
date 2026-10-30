# 题目：2493. 将节点分成尽可能多的组（Divide Nodes Into the Maximum Number of Groups）
# 思路：先用 BFS 判二分图（相邻层差必须为 1），再对每个连通块取「任一点为源 BFS 的最大层数」，按最小编号根汇总求和。
# 时间复杂度：O(n(n+m))，每个点各做一次 BFS；空间复杂度：O(n+m)，邻接表、dist 数组与队列。
class Solution:  # LeetCode 约定的题解类
    def magnificentSets(self, n: int, edges: List[List[int]]) -> int:  # n 是节点数（编号 1..n），edges 是边的端点列表，二分图不成立时返回 -1
        g = [[] for _ in range(n)]  # 邻接表，下标 0..n-1
        for a, b in edges:  # 遍历每条无向边
            g[a - 1].append(b - 1)  # 输入编号从 1 开始，转成 0 起下标后加边
            g[b - 1].append(a - 1)  # 反向再加一条，构成无向图
        d = defaultdict(int)  # 按连通块根记录该块能达到的最大组数，缺省为 0
        for i in range(n):  # 以每个点作为 BFS 源，求它所在连通块的候选组数
            q = deque([i])  # BFS 队列，初始只有源点
            dist = [0] * n  # 本轮 BFS 的层次数组，0 表示未访问
            dist[i] = mx = 1  # 源点在第 1 组；mx 记录当前 BFS 的最大层数
            root = i  # 记录本轮访问过的最小编号，作为连通块代表
            while q:  # 队列非空时继续 BFS
                a = q.popleft()  # 取出队首节点
                root = min(root, a)  # 连通块代表取访问过的点中最小的编号
                for b in g[a]:  # 遍历 a 的每个邻居
                    if dist[b] == 0:  # 邻居还没分层
                        dist[b] = dist[a] + 1  # 相邻节点的组号必须相差 1
                        mx = max(mx, dist[b])  # 更新当前 BFS 的最大层数
                        q.append(b)  # 邻居入队继续扩展
                    elif abs(dist[b] - dist[a]) != 1:  # 已分层但层差不为 1，说明出现奇环，无法按要求分组
                        return -1  # 不是二分图，直接返回 -1
            d[root] = max(d[root], mx)  # 同一连通块取最大的 BFS 层数作为该块贡献
        return sum(d.values())  # 各连通块贡献之和即最多组数
