# 题目：2642. 设计可以求最短路径的图类（Design Graph With Shortest Path Calculator）
# 思路：邻接矩阵存有向边，最短路用朴素 Dijkstra：每轮选出未访问的最近点，再用它松弛所有节点。
# 时间复杂度：构造 O(n^2)，加边 O(1)，单次最短路 O(n^2)；空间复杂度：O(n^2)，邻接矩阵。
class Graph:  # 题目要求实现的图类
    def __init__(self, n: int, edges: List[List[int]]):  # n：节点数；edges：初始有向边 [from, to, cost]
        self.n = n  # 保存节点数，供后面的方法使用
        self.g = [[inf] * n for _ in range(n)]  # 邻接矩阵初始化为「无穷大」，表示暂不可达
        for f, t, c in edges:  # 逐条写入初始边
            self.g[f][t] = c  # 有向边写入邻接矩阵

    def addEdge(self, edge: List[int]) -> None:  # 动态增加一条有向边
        f, t, c = edge  # 拆出起点、终点、边权
        self.g[f][t] = c  # 直接写入矩阵，题目保证这些边不会相互冲突

    def shortestPath(self, node1: int, node2: int) -> int:  # 求最短路，不可达返回 -1
        dist = [inf] * self.n  # dist[j] 是 node1 到 j 的当前最短距离估计
        dist[node1] = 0  # 起点到自身的距离为 0
        vis = [False] * self.n  # vis[j] 标记 j 的最短距离是否已经确定
        for _ in range(self.n):  # 最多 n 轮，每轮确定一个节点
            t = -1  # t 记录本轮要确定的节点，-1 表示还没选出来
            for j in range(self.n):  # 在未确定的节点里找距离最小的那个
                if not vis[j] and (t == -1 or dist[t] > dist[j]):  # j 未确定，且比当前候选更近
                    t = j  # 更新候选节点
            vis[t] = True  # 最近的节点距离已经可以确定，标记为已访问
            for j in range(self.n):  # 用 t 去松弛它所有的出边
                dist[j] = min(dist[j], dist[t] + self.g[t][j])  # 经 t 中转是否更短，取较小值
        return -1 if dist[node2] == inf else dist[node2]  # 仍是「无穷大」说明不可达，返回 -1


# Your Graph object will be instantiated and called as such:  # 判题器给出的调用示例
# obj = Graph(n, edges)  # 构造图对象
# obj.addEdge(edge)  # 动态加一条边
# param_2 = obj.shortestPath(node1,node2)  # 查询最短路径长度
