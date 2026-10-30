# 题目：2065. 最大化一张图中的路径价值（Maximum Path Quality of a Graph）
# 思路：DFS 枚举从 0 号点出发、总耗时不超过 maxTime 的所有路径；节点只在本次路径首次到达时累加价值，回到 0 号点就更新答案。
# 时间复杂度：O(b^maxTime)，b 为平均度数，路径数随 maxTime 指数增长；空间复杂度：O(n + E)，用于邻接表与递归栈。
class Solution:  # LeetCode 约定的题解类
    def maximalPathQuality(  # values 是各节点价值，edges 是带耗时的边，maxTime 是允许总耗时
        self, values: List[int], edges: List[List[int]], maxTime: int  # 参数拆成多行书写，原写法保持不变
    ) -> int:  # 返回能获得的最大路径价值
        def dfs(u: int, cost: int, value: int):  # 内嵌 DFS：u 当前节点，cost 已花时间，value 当前累计价值
            if u == 0:  # 回到起点 0 号点，结算一条闭环路径
                nonlocal ans  # ans 在外层函数里定义，这里要修改它必须声明 nonlocal
                ans = max(ans, value)  # 用当前价值刷新最大值
            for v, t in g[u]:  # 枚举 u 的全部邻接边
                if cost + t <= maxTime:  # 剪枝：加上这条边的耗时后仍不能超过 maxTime
                    if vis[v]:  # 邻居已经在当前路径上出现过
                        dfs(v, cost + t, value)  # 重复节点不重复计价值，价值保持不变继续搜
                    else:  # 否则是本路径第一次访问该节点
                        vis[v] = True  # 先标记已访问，防止同一节点价值被重复累加
                        dfs(v, cost + t, value + values[v])  # 首次访问才累加 values[v]
                        vis[v] = False  # 回溯：撤销标记，供其它搜索分支使用

        n = len(values)  # 节点个数
        g = [[] for _ in range(n)]  # 邻接表 g[u] 保存 (邻居, 边耗时) 二元组
        for u, v, t in edges:  # 遍历每条无向边，建双向图
            g[u].append((v, t))  # 正向边 u → v
            g[v].append((u, t))  # 反向边 v → u
        vis = [False] * n  # vis 标记节点是否在当前路径上
        vis[0] = True  # 起点 0 号点一开始就在路径上
        ans = 0  # 记录最大路径价值
        dfs(0, 0, values[0])  # 从 0 号点出发，耗时 0，初始价值为 values[0]
        return ans  # 返回搜索得到的最大路径价值
