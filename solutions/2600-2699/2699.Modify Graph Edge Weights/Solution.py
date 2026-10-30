# 题目：2699. 修改图中的边权（Modify Graph Edge Weights）
# 核心思路：先把 -1 边视为不存在求最短路。若已知边已使最短路小于 target 则无解；否则按顺序把每条待定边设为 1 再求最短路，一旦最短路不超过 target 就把这条边加长 target - d 使最短路恰为 target，其余待定边全设无穷大。
# 时间复杂度：O(m * (n^2 + m))，m 为边数，每修改一条待定边就跑一次 O(n^2+m) 的朴素 Dijkstra；空间复杂度：O(n^2)，邻接矩阵。
class Solution:  # LeetCode 约定的题解类
    def modifiedGraphEdges(  # n：结点数；edges：边表（权值 -1 表示待定）；source/destination：起点终点；target：目标最短路
        self, n: int, edges: List[List[int]], source: int, destination: int, target: int
    ) -> List[List[int]]:  # 返回修改后的边表，无解时返回空列表
        def dijkstra(edges: List[List[int]]) -> int:  # 内部函数：按当前 edges 求 source 到 destination 的最短路
            g = [[inf] * n for _ in range(n)]  # 邻接矩阵，inf 表示两点之间没有边
            for a, b, w in edges:  # 遍历所有边，把已有权重的边写进矩阵
                if w == -1:  # 权值为 -1 的待定边当前还没有可用权重
                    continue  # 跳过，相当于这条边不存在
                g[a][b] = g[b][a] = w  # 无向图，两个方向都要连上
            dist = [inf] * n  # dist[i]：source 到 i 的当前最短距离
            dist[source] = 0  # 源点到自身的距离为 0
            vis = [False] * n  # vis[i]：i 的最短距离是否已经确定
            for _ in range(n):  # 一共要确定 n 个点的最短距离
                k = -1  # k：本轮被选中的距离最小的未确定点，-1 表示还没选
                for j in range(n):  # 在尚未确定的点里找 dist 最小的那个
                    if not vis[j] and (k == -1 or dist[k] > dist[j]):  # k == -1 时无条件赋值，否则与当前最优比较
                        k = j  # 记录本轮候选点
                vis[k] = True  # 该点的最短距离就此确定
                for j in range(n):  # 用 k 去松弛所有点
                    dist[j] = min(dist[j], dist[k] + g[k][j])  # 松弛：从 k 绕一下是否比原来更短
            return dist[destination]  # source → destination 的最短路，不可达时返回 inf

        inf = 2 * 10**9  # 无穷大：2e9 大于任何合法边权，又不会引入浮点误差
        d = dijkstra(edges)  # 先只用已知权重的边求一次最短路
        if d < target:  # 已知边已把最短路压到 target 以下，边权只能变大，故无解
            return []  # 无解返回空列表
        ok = d == target  # 若已知边最短路恰好是 target，待定边只要设成极大值即可
        for e in edges:  # 按顺序逐条处理边
            if e[2] > 0:  # 权值已确定的边不允许修改
                continue  # 跳过这条边
            if ok:  # 最短路已等于 target，剩下待定边不能再缩短它
                e[2] = inf  # 设成极大值，等价于不参与任何最短路
                continue  # 处理下一条
            e[2] = 1  # 先把这条待定边试探性地设成最小合法权 1
            d = dijkstra(edges)  # 边权变了，重新求最短路
            if d <= target:  # 这条边落在了某条长度不超过 target 的最短路上
                ok = True  # 最短路已锁定，后面的待定边都可以设为极大值
                e[2] += target - d  # 把这条边加长 target - d，使最短路正好等于 target
        return edges if ok else []  # 能凑出 target 就返回修改后的边表，否则返回空列表
