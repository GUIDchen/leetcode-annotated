# 题目：2846. 边权重均等查询（Minimum Edge Weight Equilibrium Queries in a Tree）
# 思路：BFS 预处理每点到根路径上各边权的出现次数，用倍增表求 LCA；u→v 路径边数减去出现最多的那种边权的边数，就是需要改动的边数。
# 时间复杂度：O((n + q) * (log n + 26))；空间复杂度：O(n * (log n + 26))，用于倍增表与边权计数。
class Solution:  # LeetCode 约定的题解类
    def minOperationsQueries(  # n：结点数；edges：带权无向边；queries：询问的结点对
        self, n: int, edges: List[List[int]], queries: List[List[int]]  # 参数续行：起点、边表、询问表
    ) -> List[int]:  # 返回每个询问的答案列表
        m = n.bit_length()  # 倍增层数：2^m >= n，即 n 的二进制位数
        g = [[] for _ in range(n)]  # 邻接表：g[u] 存 (相邻结点 v, 0 基边权)
        f = [[0] * m for _ in range(n)]  # 倍增祖先表：f[i][j] 是 i 的第 2^j 级祖先
        p = [0] * n  # 每个结点的直接父结点
        cnt = [None] * n  # cnt[i][c]：根到 i 的路径上边权 c 出现的次数（先占位）
        depth = [0] * n  # 每个结点的深度，根为 0
        for u, v, w in edges:  # 遍历边表，构建无向邻接表
            g[u].append((v, w - 1))  # 从 u 出发的边，边权减 1 换成 0..25 的下标
            g[v].append((u, w - 1))  # 从 v 出发的边（无向边双向加入）
        cnt[0] = [0] * 26  # 根的路径上没有任何边，26 种边权计数全为 0
        q = deque([0])  # BFS 队列，从根结点 0 开始
        while q:  # 逐层遍历整棵树
            i = q.popleft()  # 取得队首结点
            f[i][0] = p[i]  # 第 2^0 = 1 级祖先就是直接父亲
            for j in range(1, m):  # 由低到高递推更高层的祖先
                f[i][j] = f[f[i][j - 1]][j - 1]  # 2^j 级祖先 = 2^(j-1) 级祖先再往上 2^(j-1) 级
            for j, w in g[i]:  # 遍历 i 的所有邻居
                if j != p[i]:  # 跳过父亲，避免沿原路边往回走
                    p[j] = i  # 记录 j 的父亲是 i
                    cnt[j] = cnt[i][:]  # 继承父结点的路径边权计数
                    cnt[j][w] += 1  # 把 i→j 这条边权为 w 的边计入 j 的路径统计
                    depth[j] = depth[i] + 1  # 子结点深度 = 父结点深度 + 1
                    q.append(j)  # 子结点入队，等待继续向下扩展
        ans = []  # 每个询问的答案
        for u, v in queries:  # 逐个处理询问
            x, y = u, v  # 用副本 x / y 做上跳，保留原始端点 u / v 供最后统计
            if depth[x] < depth[y]:  # 保证 x 是较深的那个
                x, y = y, x  # 交换，使 depth[x] >= depth[y]
            for j in reversed(range(m)):  # 从高位到低位把较深的 x 提到与 y 同深度
                if depth[x] - depth[y] >= (1 << j):  # 高度差够 2^j 层才跳，避免跳过
                    x = f[x][j]  # x 上跳 2^j 层
            for j in reversed(range(m)):  # x 与 y 同步上跳，寻找最近公共祖先
                if f[x][j] != f[y][j]:  # 祖先不同说明还没越过 LCA，可以继续上跳
                    x, y = f[x][j], f[y][j]  # x、y 同时上跳 2^j 层
            if x != y:  # 若此时还没重合，LCA 是二者的共同父亲
                x = p[x]  # 再上跳一层得到 LCA
            mx = max(cnt[u][j] + cnt[v][j] - 2 * cnt[x][j] for j in range(26))  # 树上差分：u→v 路径上权值为 j 的边数 = cnt[u][j] + cnt[v][j] - 2 * cnt[lca][j]，取最大值
            ans.append(depth[u] + depth[v] - 2 * depth[x] - mx)  # 路径总边数减去保留最多的那种边权，剩下的就是要改的边数
        return ans  # 返回所有询问的结果
