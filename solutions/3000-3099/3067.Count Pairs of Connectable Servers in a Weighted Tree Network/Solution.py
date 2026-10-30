# 题目：3067. 在带权树网络中统计可连接服务器对数目（Count Pairs of Connectable Servers in a Weighted Tree Network）
# 核心思路：枚举每个服务器作为中心，对它去掉后得到的每条分支各做一次 DFS 统计「到中心距离是 signalSpeed 整数倍」的节点数，再用「已累计节点数 × 当前分支节点数」累加跨分支的配对。
# 时间复杂度：O(n²)，n 个中心各 DFS 一次；空间复杂度：O(n)，邻接表 O(n) 加递归栈 O(n)。
class Solution:  # LeetCode 约定的题解类
    def countPairsOfConnectableServers(  # edges：带权树的边集；signalSpeed：信号速度；返回每个服务器可连接的服务器对数
        self, edges: List[List[int]], signalSpeed: int  # 参数：self 为实例本身，edges 边集，signalSpeed 信号速度
    ) -> List[int]:  # 返回值为每个服务器的可连接对数列表
        def dfs(a: int, fa: int, ws: int) -> int:  # 内部递归函数：从 a 出发、父节点 fa、到 a 的路径权和 ws，返回该分支中 distance % signalSpeed == 0 的节点数
            cnt = 0 if ws % signalSpeed else 1  # 起点 a 自身：权和能被 signalSpeed 整除就计 1，否则计 0（Python 的 0 为假走前面的 0）
            for b, w in g[a]:  # 遍历 a 的所有邻居，解包出邻居 b 与边权 w
                if b != fa:  # 跳过父节点 fa，避免走回头路重复搜索
                    cnt += dfs(b, a, ws + w)  # 深入子树，路径权和累加 w，并把子结果累加进 cnt
            return cnt  # 返回本分支内符合条件的节点总数

        n = len(edges) + 1  # 节点数等于边数加一
        g = [[] for _ in range(n)]  # 邻接表：g[v] 存放 (相邻节点, 边权) 的列表，先建 n 个空表
        for a, b, w in edges:  # 逐条边建无向图
            g[a].append((b, w))  # a 的邻接表追加 (b, w)
            g[b].append((a, w))  # b 的邻接表追加 (a, w)，反向边也要登记
        ans = [0] * n  # 答案数组，ans[a] 表示以 a 为中心的服务器对数
        for a in range(n):  # 枚举每个节点 a 作为中心服务器
            s = 0  # s：已处理分支中符合条件的节点总数
            for b, w in g[a]:  # 枚举 a 的每条分支；去掉 a 后各分支互不连通
                t = dfs(b, a, w)  # 当前分支内符合条件的节点数
                ans[a] += s * t  # 与之前所有分支的节点两两配对，累加 s * t
                s += t  # 把当前分支节点数并入 s，供后续分支配对
        return ans  # 返回所有服务器的可连接对数列表
