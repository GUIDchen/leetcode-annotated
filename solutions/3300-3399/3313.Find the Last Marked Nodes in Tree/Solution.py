# 题目：3313. 查找树中最后标记的节点（Find the Last Marked Nodes in Tree）🔒
# 核心思路：先从节点 0 出发 DFS 求最远点 a，再从 a 求最远点 b，a、b 就是树直径的两端；每个节点比较到 a、b 的距离，取更远的那端作为最后标记它的节点。
# 时间复杂度：三次 DFS 合计 O(n)；空间复杂度：O(n)，用于邻接表与三个距离数组。
class Solution:  # LeetCode 约定的题解类
    def lastMarkedNodes(self, edges: List[List[int]]) -> List[int]:  # edges：树的 n-1 条无向边；返回每个节点最后被标记的邻居编号
        def dfs(i: int, fa: int, dist: List[int]):  # i：当前节点；fa：父节点（防回环）；dist：距离数组
            for j in g[i]:  # 枚举当前节点的所有邻居
                if j != fa:  # 跳过父节点，避免在树上走回头路
                    dist[j] = dist[i] + 1  # 子节点距离 = 当前节点距离 + 1
                    dfs(j, i, dist)  # 递归进入子节点，当前节点成为它的父节点

        n = len(edges) + 1  # 边数 +1 即节点个数
        g = [[] for _ in range(n)]  # 邻接表：g[u] 保存 u 的所有邻居
        for u, v in edges:  # 逐条边建无向图
            g[u].append(v)  # u 的邻居中加入 v
            g[v].append(u)  # v 的邻居中加入 u（无向边双向记录）

        dist1 = [-1] * n  # dist1[i]：节点 i 到起点 0 的距离，-1 表示还没访问到
        dist1[0] = 0  # 起点到自己的距离是 0
        dfs(0, -1, dist1)  # 从节点 0 出发 DFS 填距离
        a = dist1.index(max(dist1))  # 离 0 最远的点可以取作直径的一个端点 a

        dist2 = [-1] * n  # dist2[i]：节点 i 到端点 a 的距离
        dist2[a] = 0  # a 到自己的距离是 0
        dfs(a, -1, dist2)  # 以 a 为根再跑一次 DFS
        b = dist2.index(max(dist2))  # 离 a 最远的点就是直径的另一个端点 b

        dist3 = [-1] * n  # dist3[i]：节点 i 到端点 b 的距离
        dist3[b] = 0  # b 到自己的距离是 0
        dfs(b, -1, dist3)  # 以 b 为根再跑一次 DFS

        return [a if x > y else b for x, y in zip(dist2, dist3)]  # 逐点比较：到 a 更远就被 a 最后标记，否则（含相等）被 b 标记
