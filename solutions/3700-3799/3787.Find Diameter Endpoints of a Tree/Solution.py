# 题目：3787. 查找树的直径端点（Find Diameter Endpoints of a Tree）
# 核心思路：从任意点 BFS 得到直径端点 a，再从 a BFS 得到另一端点 b 与 dist1，最后从 b BFS 得到 dist2；直径长度为 dist1[b]，距 a 或距 b 等于该长度的点都是直径端点。
# 复杂度：时间 O(n)，三次 BFS 均为线性；空间 O(n)，邻接表加距离数组。
class Solution:  # LeetCode 约定的题解类
    def findSpecialNodes(self, n: int, edges: List[List[int]]) -> str:  # 返回长度为 n 的字符串，第 i 位为 '1' 表示节点 i 是某条直径路径的端点
        g = [[] for _ in range(n)]  # 邻接表建图
        for a, b in edges:  # 逐条读入无向边
            g[a].append(b)  # a 的邻居里加入 b
            g[b].append(a)  # b 的邻居里加入 a

        def bfs(start: int):  # 内部函数：从 start 出发 BFS，返回 (最远点, 到各点的距离)
            dist = [-1] * n  # 距离数组初值 -1，兼作未访问标记
            dist[start] = 0  # 起点到自身的距离为 0
            q = deque([start])  # BFS 用的双端队列
            far = start  # far 记录已发现的离 start 最远的点
            while q:  # 队列非空就继续扩展
                u = q.popleft()  # 弹出队首节点
                if dist[u] > dist[far]:  # 距离更大就更新最远点
                    far = u  # 遍历 u 的邻居
                for v in g[u]:  # 只从距离尚未确定的邻居扩展
                    if dist[v] == -1:  # 邻居距离 = u 的距离 + 1
                        dist[v] = dist[u] + 1  # 邻居入队
                        q.append(v)  # 返回最远点与距离数组
            return far, dist
  # 第一次 BFS：从任意点 0 出发找到直径的一个端点 a
        a, _ = bfs(0)  # 第二次 BFS：从 a 出发找到另一端点 b，并留下 a 到各点的距离 dist1
        b, dist1 = bfs(a)  # 第三次 BFS：从 b 出发得到 b 到各点的距离 dist2
        _, dist2 = bfs(b)  # 直径长度等于 a 到 b 的距离
        d = dist1[b]  # 结果数组初始全为 "0"
        ans = ["0"] * n  # 逐个节点判断它是否为某条直径的端点
        for i in range(n):  # 到 a 或到 b 的距离等于直径长度，则该点是某条直径的一端
            if dist1[i] == d or dist2[i] == d:  # 标记为特殊节点
                ans[i] = "1"  # 拼成字符串返回
        return "".join(ans)  # 方法结束
