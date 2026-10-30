# 题目：3243. 新增道路查询后的最短距离 I（Shortest Distance After Road Addition Queries I）
# 思路：初始图是链 0->1->...->(n-1)，每次加边后用 BFS 重新求 0 到 n-1 的最短距离。
# 时间复杂度：O(q·(n+m))，每次查询跑一遍 BFS；空间复杂度：O(n+m)，邻接表、队列与访问数组。
class Solution:  # # LeetCode 约定的题解类
    def shortestDistanceAfterQueries(  # # 主方法：n 是城市数，queries 是依次新增的有向道路
        self, n: int, queries: List[List[int]]  # # self 是实例本身，n 为节点数，queries 为新增道路列表
    ) -> List[int]:  # # 返回每次加边后 0 到 n-1 的最短距离列表
        def bfs(i: int) -> int:  # # 内部 BFS：从起点 i 出发求到 n-1 的最短边数
            q = deque([i])  # # BFS 队列，初始只有起点
            vis = [False] * n  # # 访问标记数组，防止同一个点被重复入队
            vis[i] = True  # # 起点先标记为已访问
            d = 0  # # d 表示当前已经走过的边数，每扩一层就加一
            while 1:  # # 逐层扩展，直到终点被弹出
                for _ in range(len(q)):  # # 一次只处理当前队列中的一整层节点，保证这一层距离都是 d
                    u = q.popleft()  # # 弹出队首节点 u
                    if u == n - 1:  # # 如果已经到达终点 n-1
                        return d  # # 当前层数就是最短距离，直接返回
                    for v in g[u]:  # # 枚举 u 的所有出边
                        if not vis[v]:  # # 只把还没访问过的邻居加入队列
                            vis[v] = True  # # 入队前先打上访问标记，避免同一节点重复入队
                            q.append(v)  # # 邻居入队，留到下一层扩展
                d += 1  # # 一层处理完，距离加一

        g = [[i + 1] for i in range(n - 1)]  # # 初始图：i 到 i+1 有边，最后一个点没有出边
        ans = []  # # ans 保存每次加边后的最短距离
        for u, v in queries:  # # 依次处理每条新增道路
            g[u].append(v)  # # 把有向边 u -> v 加入邻接表
            ans.append(bfs(0))  # # 加边后重新从 0 号城市跑一次 BFS，并把结果记入答案
        return ans  # # 返回所有查询的答案
