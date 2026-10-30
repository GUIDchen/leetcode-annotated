# 题目：3372. 连接两棵树后最大目标节点数目 I（Maximize the Number of Target Nodes After Connecting Trees I）
# 思路：目标节点是与连接点在 k 步以内的节点。第二棵树任选一点作连接点，只消耗 1 条边，对每个点做 DFS 取最大贡献 t；再对第一棵树每个点统计距离 ≤ k 的节点数并与 t 相加。
# 时间复杂度：O(n·m)，n、m 为两棵树节点数，每个节点都做一次 DFS；空间复杂度：O(n+m)，邻接表与递归栈。
class Solution:  # LeetCode 约定的题解类
    def maxTargetNodes(  # maxTargetNodes：edges1/edges2 是两棵树的边，k 是最大距离
        self, edges1: List[List[int]], edges2: List[List[int]], k: int  # 参数列表的第二行：self 与三个输入参数
    ) -> List[int]:  # 返回每个节点作为连接点时可得到的目标节点数列表
        def build(edges: List[List[int]]) -> List[List[int]]:  # 内部函数：把边列表转换成邻接表
            n = len(edges) + 1  # 节点数 = 边数 + 1
            g = [[] for _ in range(n)]  # 初始化 n 个空的邻接表
            for a, b in edges:  # 遍历每条无向边
                g[a].append(b)  # a -> b 这条边
                g[b].append(a)  # b -> a，双向存储
            return g  # 返回建好的图

        def dfs(g: List[List[int]], a: int, fa: int, d: int) -> int:  # 内部函数：统计与节点 a 距离不超过 d 的节点数（fa 是父节点，防止走回头路）
            if d < 0:  # 距离预算为负，走不动了
                return 0  # 返回 0 个可达节点
            cnt = 1  # 自己算 1 个目标节点
            for b in g[a]:  # 遍历 a 的所有邻居
                if b != fa:  # 跳过父节点，避免在树上原地打转
                    cnt += dfs(g, b, a, d - 1)  # 预算减 1，递归累加子树的贡献
            return cnt  # 返回该子树的节点数

        g2 = build(edges2)  # 建第二棵树的邻接表
        m = len(edges2) + 1  # 第二棵树的节点数 = 边数 + 1
        t = max(dfs(g2, i, -1, k - 1) for i in range(m))  # 第二棵树的最大贡献：连接消耗 1 条边，所以预算为 k-1
        g1 = build(edges1)  # 建第一棵树的邻接表
        n = len(edges1) + 1  # 第一棵树的节点数 = 边数 + 1
        return [dfs(g1, i, -1, k) + t for i in range(n)]  # 第一棵树内距离 ≤ k 的节点数，加上第二棵树的贡献 t
