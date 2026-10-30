# 题目：2608. 图中的最短环（Shortest Cycle in a Graph）
# 思路：枚举每条边并临时删除它，用 BFS 求两端点之间的最短路，最短路长度 + 1 就是经过该边的环长，全部取最小。
# 时间复杂度：O(E(V + E))，每条边做一次 BFS；空间复杂度：O(V + E)，邻接表加距离数组。
class Solution:  # LeetCode 约定的题解类
    def findShortestCycle(self, n: int, edges: List[List[int]]) -> int:  # n 是点数，edges 是边表，返回最短环长度
        def bfs(u: int, v: int) -> int:  # 内部函数：临时删掉边 (u,v)，求 u 到 v 的最短路
            dist = [inf] * n  # dist[i]：从 u 到 i 的最短距离，先全部设为无穷
            dist[u] = 0  # 起点到自己的距离为 0
            q = deque([u])  # BFS 队列，初始只有起点 u
            while q:  # 队列非空就继续扩展
                i = q.popleft()  # 弹出队首
                for j in g[i]:  # 遍历 i 的所有邻居
                    if (i, j) != (u, v) and (j, i) != (u, v) and dist[j] == inf:  # 跳过被删掉的边 (u,v)/(v,u) 以及已访问的点
                        dist[j] = dist[i] + 1  # 记录从 u 到 j 的距离
                        q.append(j)  # 新点入队，等待扩展
            return dist[v] + 1  # 最短路长度 + 1（补回被删的边）就是环长

        g = defaultdict(set)  # 邻接表：用集合自动去重，避免重边干扰 BFS
        for u, v in edges:  # 遍历每条无向边
            g[u].add(v)  # 建正向边 u -> v
            g[v].add(u)  # 建反向边 v -> u
        ans = min(bfs(u, v) for u, v in edges)  # 枚举每条边作为被删的那一条，取最小环长
        return ans if ans < inf else -1  # 无环时返回 -1
