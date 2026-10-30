# 题目：1059. 从起点到终点的所有路径（All Paths from Source Lead to Destination）
# 思路：建邻接表后从 source 做 DFS，用三色标记（0 未访问、1 访问中、2 已验证）检测环，并要求所有死胡同节点都必须是 destination。
# 时间复杂度：O(n + E)，每个点与每条边只处理一次；空间复杂度：O(n + E)，邻接表与状态数组。
class Solution:  # LeetCode 约定的题解类
    def leadsToDestination(  # 判断从起点出发的所有路径是否都终止于终点
        self, n: int, edges: List[List[int]], source: int, destination: int  # n 个节点、有向边列表、起点、终点
    ) -> bool:  # 返回布尔结论
        def dfs(i: int) -> bool:  # 判断以 i 为起点的所有路径是否合法
            if st[i]:  # 该节点已经访问过
                return st[i] == 2  # 状态 2 表示已验证通过；状态 1 表示成环，返回假
            if not g[i]:  # 死胡同节点（没有出边）
                return i == destination  # 只有恰好是终点才合法

            st[i] = 1  # 标记为「访问中」，供环检测使用
            for j in g[i]:  # 遍历所有后继节点
                if not dfs(j):  # 任一后继路径不合法
                    return False  # 整体返回假
            st[i] = 2  # 所有后继都合法，标记为已验证
            return True  # 以 i 为起点的路径全部合法

        g = [[] for _ in range(n)]  # 邻接表，初始化 n 个空列表
        for a, b in edges:  # 遍历每条有向边
            g[a].append(b)  # 建立 a -> b 的边
        if g[destination]:  # 终点还有出边，说明存在路径不在终点结束
            return False  # 直接返回假

        st = [0] * n  # 所有节点初始状态为 0（未访问）
        return dfs(source)  # 从起点开始 DFS
