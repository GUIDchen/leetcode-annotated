# 3807. Minimum Cost to Repair Edges to Traverse a Graph | 修复边以遍历图的最小成本
# 核心思路：先按代价升序排序边，二分“只允许使用前 idx+1 条最便宜的边”的前缀，再用 BFS 的层数判断 0 到 n-1 的最短路是否不超过 k 条边；最小的可行前缀末端那条边的代价即答案。
# 复杂度：时间 O(m log m + (n + m) log m)（排序 + log m 次 BFS）；空间 O(n + m)。
class Solution:  # 定义题解类
    def minCost(self, n: int, edges: List[List[int]], k: int) -> int:  # 返回从 0 到 n-1、且路径边数不超过 k 时的最小修复代价
        def check(idx: int) -> bool:  # check(idx)：只使用前 idx+1 条最便宜的边，判断能否在不超过 k 条边内走到 n-1
            g = [[] for _ in range(n)]  # 为本次判定重建邻接表，n 个空列表
            for u, v, _ in edges[: idx + 1]:  # 枚举前缀中所有可用的边（第三个字段代价在这里用不到）
                g[u].append(v)  # 加入 u -> v
                g[v].append(u)  # 加入 v -> u，无向图双向建边
            q = [0]  # BFS 的当前层队列，起点 0 入队
            dist = 0  # dist 表示当前层号，也就是已走过的边数
            vis = [False] * n  # 访问标记数组，初始全部未访问
            vis[0] = True  # 起点标记为已访问
            while q:  # 按层推进 BFS
                nq = []  # 收集下一层的节点
                for u in q:  # 遍历当前层的每个节点
                    if u == n - 1:  # 到达终点
                        return dist <= k  # 边数不超过 k 才可行
                    for v in g[u]:  # 扩展 u 的邻居
                        if not vis[v]:  # 邻居尚未访问
                            vis[v] = True  # 标记为已访问，防止重复入队
                            nq.append(v)  # 放进下一层
                q = nq  # 队列切换到下一层
                dist += 1  # 层号（边数）加一
            return False  # 不可达或步数超过 k，判定失败

        m = len(edges)  # 边的总条数
        edges.sort(key=lambda x: x[2])  # 按代价升序排序（后续二分依赖这个顺序）
        l, r = 0, m - 1  # 二分区间：最小可行前缀下标 [l, r]
        while l < r:  # 二分查找最小的可行下标
            mid = (l + r) >> 1  # 取中点
            if check(mid):  # 只用前 mid+1 条边就已经可行
                r = mid  # 答案可能更小，收缩右端
            else:  # 该前缀不可行
                l = mid + 1  # 必须放开更多（更贵的）边
        return edges[l][2] if check(l) else -1  # 可行时第 l 条边是该前缀中最贵的一条，其代价即答案；否则返回 -1
