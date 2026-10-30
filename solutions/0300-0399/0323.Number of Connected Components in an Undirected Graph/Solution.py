# 题目：323. 无向图中连通分量的数目（Number of Connected Components in an Undirected Graph）
# 思路：按边建无向邻接表，再从每个未访问节点出发做一次 DFS，能新起一次搜索就说明多了一个连通分量。
# 时间复杂度：O(n + e)，n 为节点数、e 为边数；空间复杂度：O(n + e)，邻接表与访问标记。
class Solution:  # LeetCode 约定的题解类
    def countComponents(self, n: int, edges: List[List[int]]) -> int:  # n 是节点数，edges 是无向边列表，返回连通分量的个数
        def dfs(i: int) -> int:  # dfs 返回 1 表示这里发现了一个新的连通分量，返回 0 表示节点已访问过
            if i in vis:  # 该节点已经访问过，不必重复搜索
                return 0  # 不是新分量，贡献 0
            vis.add(i)  # 标记为已访问，避免环上无限递归
            for j in g[i]:  # 沿着邻边搜遍整个连通块
                dfs(j)  # 递归访问邻居，返回值不累加，分量由最外层计一次
            return 1  # 本次调用新覆盖了一个分量，贡献 1

        g = [[] for _ in range(n)]  # 邻接表，g[u] 存放与 u 直接相连的所有节点
        for a, b in edges:  # 遍历每条无向边，把它拆成两条有向边存进邻接表
            g[a].append(b)  # a → b 这一方向
            g[b].append(a)  # b → a 这一方向
        vis = set()  # 访问标记集合；dfs 在调用时才会读取它，此时已定义
        return sum(dfs(i) for i in range(n))  # 每个节点都试一次 DFS，只有新分量才会被计入
