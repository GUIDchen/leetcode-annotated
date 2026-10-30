# 题目：2646. 最小化旅行的价格总和（Minimize the Total Price of the Trips）
# 思路：先对每条行程 DFS 统计每个节点被经过的次数，再在树上做 DP：节点减半时子节点必须原价，取两种决策的较小值。
# 时间复杂度：O(m × n)，m 为行程数、n 为节点数；空间复杂度：O(n)，邻接表、计数数组与递归栈。
class Solution:  # LeetCode 约定的题解类
    def minimumTotalPrice(  # n：节点数；edges：树边；price：每个节点价格；trips：全部行程
        self, n: int, edges: List[List[int]], price: List[int], trips: List[List[int]]
    ) -> int:  # 返回所有行程的最小价格总和
        # 第一遍 DFS：从 i 出发（fa 是父节点）搜索通往 k 的路径，路径上节点的 cnt 加一
        # 找到返回 True；若子树都没找到，说明 i 不在路径上，撤销计数
        def dfs(i: int, fa: int, k: int) -> bool:  # 路径搜索
            cnt[i] += 1  # 先假设 i 在路径上
            if i == k:  # 到达终点，路径成立
                return True  # 成功，保留计数
            ok = any(j != fa and dfs(j, i, k) for j in g[i])  # 枚举邻居：不回头走父节点，任一子树找到 k 即成功
            if not ok:  # 所有子树都没找到
                cnt[i] -= 1  # 撤销刚才多加的计数
            return ok  # 回传结果

        # 第二遍 DFS（树形 DP）：返回 (a, b)，a 是 i 不减半、b 是 i 减半时的最小价格总和
        def dfs2(i: int, fa: int) -> (int, int):  # 树形 DP
            a = cnt[i] * price[i]  # i 不减半时自身的贡献
            b = a // 2  # i 减半时自身的贡献：price 均为偶数，整除 2 即可
            for j in g[i]:  # 枚举邻居
                if j != fa:  # 跳过父节点
                    x, y = dfs2(j, i)  # x：子节点不减半的最优值；y：子节点减半的最优值
                    a += min(x, y)  # i 不减半 → 子节点可任选，取较小者
                    b += x  # i 减半 → 相邻子节点必须不减半
            return a, b  # 返回两种决策下的最小总价

        g = [[] for _ in range(n)]  # 邻接表，先建 n 个空列表
        for a, b in edges:  # 用边表建无向图
            g[a].append(b)  # a 的邻居加上 b
            g[b].append(a)  # b 的邻居加上 a
        cnt = Counter()  # 记录每个节点被经过的次数，未出现的键默认为 0
        for start, end in trips:  # 逐条行程统计路径
            dfs(start, -1, end)  # -1 表示起点没有父节点
        return min(dfs2(0, -1))  # 以 0 为根做树形 DP，取根节点两种决策的较小值
