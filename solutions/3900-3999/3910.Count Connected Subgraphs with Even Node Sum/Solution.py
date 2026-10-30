# 3910. Count Connected Subgraphs with Even Node Sum | 统计节点和为偶数的连通子图（困难）
# 核心思路：n 很小，枚举 2^n 个非空节点子集，先判断节点值之和是否为偶数；再把子集之外的位预置到访问掩码里，从子集内某点 DFS，若最终所有位都被标记，说明子集连通，计数加一。
# 复杂度：时间 O(2^n * (n + m))，m 为边数（每个子集一次求和 + 一次 DFS）；空间 O(n + m)（邻接表与递归栈）。
class Solution:  # 定义题解类
    def evenSumSubgraphs(self, nums: list[int], edges: list[list[int]]) -> int:  # 返回节点值之和为偶数、且点集本身连通的子图个数
        n = len(nums)  # 节点个数
        g = [[] for _ in range(n)]  # 邻接表，共 n 个空列表
        for u, v in edges:  # 遍历每条无向边
            g[u].append(v)  # 建立 u -> v 的单向边
            g[v].append(u)  # 建立 v -> u 的反向边，凑成无向图
        m = (1 << n) - 1  # n 位全为 1 的掩码，代表“全集”
        ans = 0  # 答案计数
        for sub in range(1, m + 1):  # 枚举所有非空的节点子集（1 .. 全集）
            s = sum(x for i, x in enumerate(nums) if sub >> i & 1)  # 当前子集内节点的取值之和
            if s % 2:  # 节点值之和为奇数，不满足题目要求
                continue  # 直接跳过该子集
            vis = m ^ sub  # 关键一步：把子集之外的位预先放进访问掩码，这样 DFS 只会在子集内部扩展

            def dfs(u: int) -> None:  # 递归函数，把与 u 连通的点都染色
                nonlocal vis  # 声明要修改外层作用域的 vis
                vis |= 1 << u  # 把 u 这一位标记为已访问
                for v in g[u]:  # 枚举 u 的所有邻居
                    if (vis >> v & 1) == 0:  # 邻居 v 还没有被访问过
                        dfs(v)  # 继续向 v 深入染色

            dfs(sub.bit_length() - 1)  # 从 sub 的最高位下标（bit_length() - 1）出发染色，该节点必定属于子集
            if vis == m:  # 若全集所有位都被标记，说明子集内部被一次 DFS 走遍，即子集连通
                ans += 1  # 连通子图计数加一
        return ans  # 返回满足条件的连通子图个数
