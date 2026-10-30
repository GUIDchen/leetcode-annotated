# 题目：1971. 寻找图中是否存在路径（Find if Path Exists in Graph）
# 思路：把无向边表建成邻接表，从 source 开始做 DFS，看能否访问到 destination。
# 时间复杂度：O(n + m)，每个点、每条边只访问一次；空间复杂度：O(n + m)，邻接表与访问集合。
class Solution:  # LeetCode 约定的题解类
    # n：点数；edges：无向边表；source/destination：起点与终点
    def validPath(
        self, n: int, edges: List[List[int]], source: int, destination: int
    ) -> bool:  # 返回从 source 能否走到 destination
        def dfs(i: int) -> bool:  # 递归 DFS：判断从点 i 出发能否到达 destination
            if i == destination:  # 已经走到终点
                return True  # 找到路径，返回成功
            vis.add(i)  # 把 i 记入已访问集合，防止绕圈造成死循环
            for j in g[i]:  # 枚举 i 的所有邻居
                if j not in vis and dfs(j):  # 邻居未访问且从它出发能到终点
                    return True  # 提前返回成功，剪掉其余分支
            return False  # 所有邻居都走不通

        g = [[] for _ in range(n)]  # 邻接表：g[u] 保存与 u 直接相连的所有点
        for u, v in edges:  # 遍历每条无向边
            g[u].append(v)  # u 的邻接表加入 v
            g[v].append(u)  # v 的邻接表加入 u（无向图要双向插入）
        vis = set()  # 已访问点集合
        return dfs(source)  # 从起点开始搜索整张图
