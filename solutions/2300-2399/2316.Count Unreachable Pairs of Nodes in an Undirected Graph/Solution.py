# 题目：2316. 统计无向图中无法互相到达点对数（Count Unreachable Pairs of Nodes in an Undirected Graph）
# 思路：用 DFS 求每个连通块的大小 t，再用前缀思想计数——当前块里每个点与之前所有块里的点都无法互相到达，一次贡献 s*t（s 为之前块的点数之和），最后累加。
# 时间复杂度：O(n + m)，每个点与每条边只访问一次（m 为边数）；空间复杂度：O(n + m)，邻接表与访问数组。
class Solution:  # LeetCode 约定的题解类
    def countPairs(self, n: int, edges: List[List[int]]) -> int:  # n：节点数；edges：无向边；返回无法互相到达的点对数量
        def dfs(i: int) -> int:  # DFS：从 i 出发遍历整个连通块，返回块内节点数
            if vis[i]:  # 已经访问过，不再重复计数
                return 0  # 返回 0，表示这个点不贡献新的节点
            vis[i] = True  # 标记当前点已访问
            return 1 + sum(dfs(j) for j in g[i])  # 自己算 1，再加上所有邻居能到达的点数

        g = [[] for _ in range(n)]  # 邻接表：g[u] 是与 u 直接相连的节点列表；它定义在 dfs 之后，但调用时才求值，闭包照样能拿到
        for a, b in edges:  # 逐条读入无向边
            g[a].append(b)  # 加入 a -> b 这条方向
            g[b].append(a)  # 加入 b -> a 这条反向，无向图必须双向添加
        vis = [False] * n  # 访问标记数组，初始全部为 False
        ans = s = 0  # ans：答案；s：已经处理过的所有连通块的节点总数
        for i in range(n):  # 枚举每个点，借此发现所有连通块
            t = dfs(i)  # t 是当前连通块的大小；已访问过的点会返回 0
            ans += s * t  # 当前块的每个点和之前块的所有点都互不可达，新增 s*t 对
            s += t  # 把当前块的点数并入 s
        return ans  # 返回无法互相到达的点对总数
