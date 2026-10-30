# 题目：1443. 收集树上所有苹果的最少时间（Minimum Time to Collect All Apples in a Tree）
# 思路：闭包写成后序 DFS，返回收集该子树苹果需要的边数；没有苹果的分支返回 0 表示不必往返。
# 时间复杂度：O(n)；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def minTime(self, n: int, edges: List[List[int]], hasApple: List[bool]) -> int:  # n 是节点数，edges 是无向边，hasApple 标记哪些节点有苹果
        def dfs(u, cost):  # u 是当前节点，cost 是进入这一分支的代价（根为 0，其它为 2）
            if vis[u]:  # 已经访问过，说明走回了父节点
                return 0  # 不需要重复走这段路
            vis[u] = True  # 标记当前节点已访问
            nxt_cost = 0  # 子树内累计路程
            for v in g[u]:  # 遍历所有邻居
                nxt_cost += dfs(v, 2)  # 向下的边要往返，所以子调用的代价是 2
            if not hasApple[u] and nxt_cost == 0:  # 自己和子树都没有苹果
                return 0  # 这条分支完全不用来
            return cost + nxt_cost  # 否则需要进入这一层，代价是 cost 加上子树内部路程

        g = defaultdict(list)  # 邻接表；defaultdict 让缺失的键自动建成空列表
        for u, v in edges:  # 逐条边建图
            g[u].append(v)  # 无向边 u → v
            g[v].append(u)  # 无向边 v → u
        vis = [False] * n  # 访问标记数组
        return dfs(0, 0)  # 从根节点 0 出发，根没有入边所以代价为 0
