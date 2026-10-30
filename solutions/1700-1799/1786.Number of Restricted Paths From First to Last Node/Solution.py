# 题目：1786. 从第一个节点出发到最后一个节点的受限路径数（Number of Restricted Paths From First to Last Node）
# 思路：以终点 n 为源用堆优化 Dijkstra 反向求出每个点到 n 的最短距离 dist，再用 @cache 记忆化 DFS 在 dist 严格递减的关系上统计路径数。
# 时间复杂度：O((n + m) log n)；空间复杂度：O(n + m)，邻接表、dist、递归缓存与堆。
class Solution:  # LeetCode 约定的题解类
    def countRestrictedPaths(self, n: int, edges: List[List[int]]) -> int:  # 返回从节点 1 到节点 n 的受限路径数（沿途 dist 必须严格递减）
        @cache  # 给 dfs 加记忆化：同样的 i 只算一次（@cache 由判题环境提供，无需 import）
        def dfs(i):  # dfs(i)：从 i 出发、每步 dist 严格减小的路径条数；闭包引用下面才定义的 g/dist/mod，调用时已就绪
            if i == n:  # 到达终点，说明这条路径合法结束
                return 1  # 终点自身算作 1 条完整路径
            ans = 0  # 累加器：统计从 i 出发的后继方案数
            for j, _ in g[i]:  # 遍历 i 的邻居 j，下划线丢弃边权（这一步只比较 dist，不用权值）
                if dist[i] > dist[j]:  # 受限条件：下一跳必须离终点更近
                    ans = (ans + dfs(j)) % mod  # 累加子问题答案并取模，避免路径数过大溢出
            return ans  # 返回方案数，@cache 会自动把结果缓存起来

        g = defaultdict(list)  # 邻接表：g[u] 保存 (邻居, 边权)，defaultdict 由判题环境提供，无需 import
        for u, v, w in edges:  # 遍历每条无向边，拆出端点 u、v 与边权 w
            g[u].append((v, w))  # 正向边：u -> v，权值 w
            g[v].append((u, w))  # 反向边：无向图所以 v -> u 也要记录
        q = [(0, n)]  # 小根堆，元素为 (距离, 节点)，从终点 n 出发反向求最短路
        dist = [inf] * (n + 1)  # dist[x]：x 到终点 n 的最短距离，先全部置为无穷大
        dist[n] = 0  # 终点到自身距离为 0
        mod = 10**9 + 7  # 取模常量，与 C++ 版本保持一致
        while q:  # 堆非空就继续松弛
            _, u = heappop(q)  # 弹出距离最小的节点，下划线丢弃距离值
            for v, w in g[u]:  # 遍历 u 的所有邻居与边权
                if dist[v] > dist[u] + w:  # 松弛条件：绕道 u 到 v 更短才更新
                    dist[v] = dist[u] + w  # 更新 v 到终点的最短距离
                    heappush(q, (dist[v], v))  # 新的 (距离, 节点) 入堆，等待继续扩散
        return dfs(1)  # 从节点 1 出发统计受限路径数
