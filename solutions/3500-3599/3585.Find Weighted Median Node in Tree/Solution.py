# 3585. 树中找到带权中位节点（Find Weighted Median Node in Tree）
# 核心思路：BFS 预处理深度、根路径距离与倍增祖先表，再用 LCA 求出查询路径总权重，最后倍增寻找路径上首个累计权重达到一半的节点。
# 复杂度：时间复杂度 O((n + q) log n)，空间复杂度 O(n log n)，其中 n 为节点数、q 为查询数。
class Solution:  # 定义题解类
    def findMedian(  # 对每个查询求出带权中位节点
        self, n: int, edges: List[List[int]], queries: List[List[int]]  # 参数：节点数、边集、查询集
    ) -> List[int]:  # 返回每个查询的中位节点编号列表
        m = n.bit_length()  # 倍增层数取 n 的二进制位数
        g = [[] for _ in range(n)]  # 邻接表，存 (邻居, 边权)
        for u, v, w in edges:  # 遍历所有边建图
            g[u].append((v, w))  # 加入正向边
            g[v].append((u, w))  # 加入反向边
        f = [[0] * m for _ in range(n)]  # 倍增表 f[i][j] 表示 i 的 2^j 级祖先
        p = [0] * n  # p 存父节点
        depth = [0] * n  # depth 存深度
        dist = [0] * n  # dist 存根到各节点的距离和
        q = deque([0])  # BFS 队列，从根节点 0 开始
        while q:  # 层序 BFS 做预处理
            i = q.popleft()  # 取出队首节点
            f[i][0] = p[i]  # 2^0 级祖先就是父节点
            for j in range(1, m):  # 递推更高层的倍增祖先
                f[i][j] = f[f[i][j - 1]][j - 1]  # 2^j 级祖先等于 2^(j-1) 级祖先的 2^(j-1) 级祖先
            for j, w in g[i]:  # 遍历当前节点的所有邻居
                if j != p[i]:  # 跳过父节点，避免走回头路
                    p[j] = i  # 记录邻居的父节点
                    depth[j] = depth[i] + 1  # 邻居深度加一
                    dist[j] = dist[i] + w  # 累加根到邻居的距离
                    q.append(j)  # 邻居入队等待处理
        ans = []  # 存放每个查询的答案
        for u, v in queries:  # 逐个处理查询
            if u == v:  # 两端点相同时路径长度为 0
                ans.append(u)  # 答案就是该节点本身
                continue  # 跳过后续计算
            x, y = u, v  # 用 x、y 同步上跳求最近公共祖先
            if depth[x] < depth[y]:  # 保证 x 是更深的一端
                x, y = y, x  # 交换使 x 更深
            for j in range(m - 1, -1, -1):  # 从高位到低位把 x 提到与 y 同深度
                if depth[x] - depth[y] >= (1 << j):  # 深度差允许跳 2^j 步时上跳
                    x = f[x][j]  # x 上跳 2^j 层
            for j in range(m - 1, -1, -1):  # 继续从高位到低位逼近最近公共祖先
                if f[x][j] != f[y][j]:  # 两个祖先不同说明还没到最近公共祖先
                    x, y = f[x][j], f[y][j]  # 两端同时上跳 2^j 层
            if x != y:  # 此时再上一层才是最近公共祖先
                x = p[x]  # x 移到真正的最近公共祖先上
            w = dist[u] + dist[v] - 2 * dist[x]  # u 到 v 的路径总权重（即两倍带权距离）
            if 2 * (dist[u] - dist[x]) >= w:  # 中位节点落在 u 到最近公共祖先这一段
                cur = u  # 从 u 开始向上爬
                for j in range(m - 1, -1, -1):  # 倍增查找最远的、仍不到一半权重的位置
                    k = f[cur][j]  # 候选祖先
                    if depth[k] >= depth[x] and 2 * (dist[u] - dist[k]) < w:  # 未越过最近公共祖先且到 u 的权重仍不足一半
                        cur = k  # 把 cur 上移到候选祖先
                ans.append(p[cur])  # cur 的父节点就是首个达到一半权重的节点
            else:  # 中位节点落在最近公共祖先到 v 这一段
                cur = v  # 从 v 开始向上爬
                for j in range(m - 1, -1, -1):  # 倍增查找最远的、距 u 已达到一半权重的位置
                    k = f[cur][j]  # 候选祖先
                    if (  # 判断候选祖先是否满足条件
                        depth[k] > depth[x]  # 严格在最近公共祖先之上
                        and 2 * (dist[u] + dist[k] - 2 * dist[x]) >= w  # 从 u 经最近公共祖先到该点的累计权重已达一半
                    ):  # 结束条件判断
                        cur = k  # 把 cur 上移到候选祖先
                ans.append(cur)  # cur 即为带权中位节点
        return ans  # 返回所有查询的答案
