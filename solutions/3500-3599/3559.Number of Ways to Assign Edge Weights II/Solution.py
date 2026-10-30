# 3559. 给边赋权值的方案数 II / Number of Ways to Assign Edge Weights II
# 核心思路：用 BFS 建树并在遍历中倍增预处理祖先表与深度，每个询问先对齐深度再用倍增求最近公共祖先，距离 d 对应的方案数为 2^(d-1)。
# 复杂度：预处理 O(n log n)，每次询问 O(log n)，空间 O(n log n)
class Solution:  # 定义解题类
    def assignEdgeWeights(  # 返回每个询问的赋权方案数
        self, edges: List[List[int]], queries: List[List[int]]  # 边列表与询问列表
    ) -> List[int]:  # 返回答案列表
        n = len(edges) + 1  # 结点数等于边数加一
        m = n.bit_length()  # 倍增层数，即 log2(n) 向上取整
        g = [[] for _ in range(n + 1)]  # 邻接表，下标从 1 开始
        for u, v in edges:  # 遍历每条边建立无向图
            g[u].append(v)  # u 的邻居加入 v
            g[v].append(u)  # v 的邻居加入 u
        f = [[0] * m for _ in range(n + 1)]  # 倍增祖先表 f[结点][层]
        p = [0] * (n + 1)  # 每个结点的父结点，根的为 0
        depth = [0] * (n + 1)  # 每个结点的深度，根为 0
        q = deque([1])  # BFS 队列，根结点 1 先入队
        while q:  # 队列非空时逐层处理
            i = q.popleft()  # 取出队首结点 i
            f[i][0] = p[i]  # 第 0 层祖先就是父结点
            for j in range(1, m):  # 递推更高层的祖先
                f[i][j] = f[f[i][j - 1]][j - 1]  # 2^j 祖先等于 2^(j-1) 祖先的 2^(j-1) 祖先
            for j in g[i]:  # 枚举结点 i 的邻居
                if j != p[i]:  # 跳过父结点，只处理子结点
                    p[j] = i  # 记录子结点的父结点
                    depth[j] = depth[i] + 1  # 子结点深度加一
                    q.append(j)  # 子结点入队
        mod = 10**9 + 7  # 取模常量
        pow2 = [1] * n  # 预处理 2 的幂表
        for i in range(1, n):  # 递推填充幂表
            pow2[i] = pow2[i - 1] * 2 % mod  # 前一项乘二再取模
        ans = []  # 保存每个询问的答案
        for u, v in queries:  # 逐个处理询问
            x, y = u, v  # 用副本向上跳，保留原来的深度值
            if depth[x] < depth[y]:  # 保证 x 是较深的那个结点
                x, y = y, x  # 交换使 x 更深
            for j in range(m - 1, -1, -1):  # 从高层到低层把 x 提到与 y 同深度
                if depth[x] - depth[y] >= (1 << j):  # 跳 2^j 步仍不会越过 y
                    x = f[x][j]  # x 向上跳 2^j 层
            for j in range(m - 1, -1, -1):  # 再从高层到低层同时上跳找分歧祖先
                if f[x][j] != f[y][j]:  # 两个祖先不同说明还没到 LCA
                    x, y = f[x][j], f[y][j]  # x、y 同时上跳到该层祖先
            if x != y:  # 仍未相遇则 LCA 是当前 x 的父结点
                x = p[x]  # 走到真正的 LCA
            d = depth[u] + depth[v] - 2 * depth[x]  # 两点间边数等于深度和的二倍 LCA 深度修正
            ans.append(0 if d == 0 else pow2[d - 1])  # 距离为 d 时方案数为 2^(d-1)
        return ans  # 返回答案列表
