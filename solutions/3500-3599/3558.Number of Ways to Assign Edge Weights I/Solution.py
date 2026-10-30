# 3558. 给边赋权值的方案数 I / Number of Ways to Assign Edge Weights I
# 核心思路：从根结点 1 到最深结点的路径有 d 条边，只要路径上出现奇数个权值 1，路径和就是奇数，故方案数为 2^(d-1)。
# 复杂度：时间 O(n)，空间 O(n)
class Solution:  # 定义解题类
    def assignEdgeWeights(self, edges: List[List[int]]) -> int:  # 返回使 1 到最深结点路径和为奇数的赋权方案数
        def dfs(i: int, fa: int = 0) -> int:  # 递归求以 i 为根、父结点为 fa 时的最大深度
            res = 0  # 记录子方向的最大深度
            for j in g[i]:  # 枚举结点 i 的邻居
                if j != fa:  # 跳过父结点，避免走回头路
                    res = max(res, dfs(j, i) + 1)  # 子方向深度加一后取最大值
            return res  # 返回最大深度

        n = len(edges) + 1  # 结点数等于边数加一
        g = [[] for _ in range(n + 1)]  # 邻接表，下标从 1 开始
        for u, v in edges:  # 遍历每条边建立无向图
            g[u].append(v)  # u 的邻居列表中加入 v
            g[v].append(u)  # v 的邻居列表中加入 u
        d = dfs(1)  # 从根结点 1 出发的最大深度
        return pow(2, d - 1, 10**9 + 7)  # 方案数为 2^(d-1)，对 1e9+7 取模
