# 题目：743. 网络延迟时间（Network Delay Time）
# 核心思路：Dijkstra 单源最短路（邻接矩阵 + 每轮线性挑最近的未访问点），取到所有节点最短时间的最大值，仍有不可达点则返回 -1。
# 时间复杂度：O(n^2 + m)，n 轮各两次 O(n) 扫描；空间复杂度：O(n^2)，邻接矩阵与距离数组。
class Solution:  # LeetCode 约定的题解类
    def networkDelayTime(self, times: List[List[int]], n: int, k: int) -> int:  # times：有向边 (u, v, w)；n：节点数；k：信号源（编号从 1 开始）
        g = [[inf] * n for _ in range(n)]  # 邻接矩阵，inf 表示两点之间暂时不可达
        for u, v, w in times:  # 逐条把有向边写进矩阵
            g[u - 1][v - 1] = w  # 节点编号 1 起始，转成 0 起始的矩阵下标
        dist = [inf] * n  # dist[i] 表示源点到 i 的最短距离，初始都不可达
        dist[k - 1] = 0  # 源点到自身的距离为 0
        vis = [False] * n  # 记录节点的最短路是否已经最终确定
        for _ in range(n):  # 至多 n 轮，每轮确定一个节点
            t = -1  # -1 表示本轮还没有选出候选点
            for j in range(n):  # 线性扫描找 dist 最小的未访问点
                if not vis[j] and (t == -1 or dist[t] > dist[j]):  # 未访问且比当前候选更近就往候选上换（t == -1 时直接接受）
                    t = j  # 把候选更新为 j
            vis[t] = True  # 选中的点最短路已经确定
            for j in range(n):  # 用 t 松弛它的所有出边
                dist[j] = min(dist[j], dist[t] + g[t][j])  # 经 t 更短就更新；inf 参与加法仍是超大数，不会错误地变优
        ans = max(dist)  # 全部节点收到信号的时间就是最大最短路
        return -1 if ans == inf else ans  # 最大值仍是 inf 说明有节点收不到信号，按题意返回 -1
