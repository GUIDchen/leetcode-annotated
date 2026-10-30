# 题目：1192. 查找集群内的关键连接（Critical Connections in a Network）
# 思路：Tarjan 求桥，DFS 中维护 dfn（访问时间）与 low（能回溯到的最小时间），满足 low[b] > dfn[a] 的树边 a-b 就是桥。
# 时间复杂度：O(n + m)，每条边每个点只访问常数次；空间复杂度：O(n + m)，含邻接表与两个数组。
class Solution:  # LeetCode 约定的题解类
    def criticalConnections(  # 返回图中所有关键连接（桥）
        self, n: int, connections: List[List[int]]  # n 个节点；connections 是无向边列表
    ) -> List[List[int]]:  # 返回值是桥组成的边列表
        def tarjan(a: int, fa: int):  # 递归函数：a 当前节点，fa 父节点
            nonlocal now  # 需要修改外层的访问时间计数器
            now += 1  # 时间戳自增，得到本次访问的序号
            dfn[a] = low[a] = now  # 记录首次访问时间，并把 low 初始化为它
            for b in g[a]:  # 遍历 a 的邻居
                if b == fa:  # 跳过父节点，避免把无向边当成回边
                    continue  # 处理下一个邻居
                if not dfn[b]:  # b 未访问，是 DFS 树边
                    tarjan(b, a)  # 递归深入 b
                    low[a] = min(low[a], low[b])  # 用 b 子树的最小可达时间更新 a 的 low
                    if low[b] > dfn[a]:  # b 的子树回不到 a，删掉 a-b 会让图断开，故为桥
                        ans.append([a, b])  # 收集这条关键连接
                else:  # b 已访问，是一条回边
                    low[a] = min(low[a], dfn[b])  # 用 b 的访问时间更新 low

        g = [[] for _ in range(n)]  # 邻接表：每个节点先放一个空列表
        for a, b in connections:  # 遍历边表建图
            g[a].append(b)  # a 连向 b
            g[b].append(a)  # b 连向 a（无向图两个方向）

        dfn = [0] * n  # dfn 初值 0 表示未访问
        low = [0] * n  # low 初值 0，会在 DFS 中被覆盖
        now = 0  # 时间戳计数器从 0 开始
        ans = []  # 结果列表
        tarjan(0, -1)  # 从 0 号节点开始 DFS，没有父节点用 -1 表示
        return ans  # 返回所有的桥
