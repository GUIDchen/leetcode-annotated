# 题目：2737. 找到最近的标记节点（Find the Closest Marked Node）
# 思路：用邻接矩阵跑朴素 Dijkstra 求出起点 s 到各点的最短路，再在所有标记节点中取最小距离，全部不可达则返回 -1。
# 时间复杂度：O(n^2 + m)，Dijkstra 是两重 n 循环；空间复杂度：O(n^2)，邻接矩阵占主导。
class Solution:  # LeetCode 约定的题解类
    def minimumDistance(  # 多行参数列表：n 节点数、edges 有向边、s 起点
        self, n: int, edges: List[List[int]], s: int, marked: List[int]  # 最后一个参数 marked 是标记节点列表
    ) -> int:  # 返回离起点最近的标记节点距离，不可达时返回 -1
        g = [[inf] * n for _ in range(n)]  # 邻接矩阵，inf 表示两点之间暂时没有边
        for u, v, w in edges:  # 逐条读入有向边
            g[u][v] = min(g[u][v], w)  # 同一对节点之间可能有多条边，只保留最小权值
        dist = [inf] * n  # dist[i] 表示起点到节点 i 的最短距离，初始全是 inf
        vis = [False] * n  # vis[i] 记录节点 i 的最短距离是否已确定
        dist[s] = 0  # 起点到自身的距离为 0
        for _ in range(n):  # 朴素 Dijkstra：循环 n 次，每次确定一个节点的最短距离
            t = -1  # t 记录本轮距离最小且尚未确定的节点，-1 表示还没选到
            for j in range(n):  # 在未确定节点中线性扫描找 dist 最小的
                if not vis[j] and (t == -1 or dist[t] > dist[j]):  # j 未确定，并且（还没选过 or 比当前候选更近）
                    t = j  # 记下本轮选中的节点
            vis[t] = True  # 把 t 的最短距离标记为已确定
            for j in range(n):  # 用 t 作为中转松弛所有节点
                dist[j] = min(dist[j], dist[t] + g[t][j])  # 若经过 t 到 j 更近就更新；g 中 inf 参与加法也不会越界
        ans = min(dist[i] for i in marked)  # 在所有标记节点中取到起点的最短距离
        return -1 if ans >= inf else ans  # 最小距离仍为 inf 说明不可达，按要求返回 -1
