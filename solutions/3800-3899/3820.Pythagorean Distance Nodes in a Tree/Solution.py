# 题目：3820. 树上的勾股距离节点（Pythagorean Distance Nodes in a Tree）
# 思路：树上没有环，任意两点的路径唯一。分别以 x、y、z 为起点做三次 BFS，得到每个节点到这三个起点的距离；把三个距离升序排序后判断是否满足勾股定理 a² + b² = c²，满足就把答案加一。
# 时间复杂度：O(n log n)，三次 BFS 各 O(n)，每个节点还有一次常数规模的排序；空间复杂度：O(n)，邻接表与三个距离数组。
class Solution:  # LeetCode 约定的题解类
    def specialNodes(
        self, n: int, edges: List[List[int]], x: int, y: int, z: int
    ) -> int:  # n：节点数；edges：树的边；x、y、z：三个给定节点
        g = [[] for _ in range(n)]  # g 是树的邻接表，初始为 n 个空列表
        for u, v in edges:  # 遍历每条边
            g[u].append(v)  # 无向边：登记 u -> v
            g[v].append(u)  # 无向边：登记 v -> u

        def bfs(i: int) -> List[int]:  # 以 i 为起点做 BFS，返回 i 到每个节点的最短距离
            q = deque([i])  # q 是 BFS 队列，起点先入队
            dist = [inf] * n  # dist[v] 是起点到节点 v 的距离，初始为无穷大表示未访问
            dist[i] = 0  # 起点到自己的距离是 0
            while q:  # 队列非空就继续向外扩展
                for _ in range(len(q)):  # 按当前层的元素个数整层处理，便于按层推进
                    u = q.popleft()  # 取出队首节点 u
                    for v in g[u]:  # 遍历 u 的每个邻居 v
                        if dist[v] > dist[u] + 1:  # 只有尚未访问过的邻居（距离仍是 inf）才会满足该条件
                            dist[v] = dist[u] + 1  # 松弛：更新 v 到起点的距离
                            q.append(v)  # v 入队，等待继续向外扩展
            return dist  # 返回起点到所有节点的距离数组

        d1 = bfs(x)  # d1[i] 是节点 i 到 x 的距离
        d2 = bfs(y)  # d2[i] 是节点 i 到 y 的距离
        d3 = bfs(z)  # d3[i] 是节点 i 到 z 的距离
        ans = 0  # ans 统计满足勾股关系的节点个数
        for a, b, c in zip(d1, d2, d3):  # 同时取出同一个节点到 x、y、z 的三个距离
            s = a + b + c  # 先保存三个距离之和，因为后面改写 a 与 c 会丢掉原值
            a, c = min(a, b, c), max(a, b, c)  # a 取最小值，c 取最大值即斜边候选
            b = s - a - c  # 用总和减去最小值和最大值，剩下的就是中间那个距离
            if a * a + b * b == c * c:  # 判断是否满足勾股定理 a² + b² = c²
                ans += 1  # 满足条件，计数加一
        return ans  # 返回满足条件的节点个数
