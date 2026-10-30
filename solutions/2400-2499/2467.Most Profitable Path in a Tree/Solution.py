# 题目：2467. 树上最大得分和路径（Most Profitable Path in a Tree）
# 核心思路：先从 Bob 出发 DFS 求出他到根 0 的路径上每个节点的到达时刻 ts；再从根 DFS 枚举每条根到叶子的路径，按 Alice 与 Bob 的到达时刻比较决定拿全额、一半还是 0 分，取最大总得分。
# 时间复杂度：O(n)，两次 DFS 各访问每个节点一次；空间复杂度：O(n)，邻接表、ts 数组与递归栈。
class Solution:  # LeetCode 约定的题解类
    def mostProfitablePath(  # 返回 Alice 能获得的最大总得分
        self, edges: List[List[int]], bob: int, amount: List[int]  # edges 是无向树的边集，bob 是 Bob 的起点，amount 是每个节点的金额
    ) -> int:  # 返回值类型：整数
        def dfs1(i, fa, t):  # dfs1：从 i 向根回溯，fa 是父节点，t 是当前时刻
            if i == 0:  # 走到根 0，说明这条链就是 Bob 到根的路径
                ts[i] = min(ts[i], t)  # 用更早的到达时刻更新 ts[i]
                return True  # 告诉上一层：它也在 Bob 到根的路径上
            for j in g[i]:  # 枚举 i 的所有邻居
                if j != fa and dfs1(j, i, t + 1):  # 跳过父节点避免走回头路，递归向根方向探测
                    ts[j] = min(ts[j], t + 1)  # j 确在路径上，记录 Bob 到达它的时刻
                    return True  # 信息继续往上回传
            return False  # 所有分支都没能到根，i 不在 Bob 到根的路径上

        def dfs2(i, fa, t, v):  # dfs2：从根往下走，t 是 Alice 到达 i 的时刻，v 是到 i 为止的累计得分
            if t == ts[i]:  # 两人同时到达：金额对半分
                v += amount[i] // 2  # 整除 2 得到一半金额
            elif t < ts[i]:  # Alice 比 Bob 先到：金额全归 Alice（若 Bob 先到则一分不得）
                v += amount[i]  # 拿下该节点的全额
            nonlocal ans  # 声明 ans 来自外层函数，下面要修改它
            if len(g[i]) == 1 and g[i][0] == fa:  # 度数为 1 且唯一邻居是父亲，说明 i 是叶子
                ans = max(ans, v)  # 走到叶子，用当前累计得分更新答案
                return  # 叶子没有子节点，回溯
            for j in g[i]:  # 枚举子节点继续往下走
                if j != fa:  # 跳过父节点，避免走回头路
                    dfs2(j, i, t + 1, v)  # 时刻加一，累计得分沿路径传递

        n = len(edges) + 1  # 树的节点数等于边数加一
        g = defaultdict(list)  # 邻接表：g[u] 保存与 u 相连的所有节点
        ts = [n] * n  # ts[i] 是 Bob 到达 i 的时刻，初始用 n 表示尚未确定
        for a, b in edges:  # 逐条边建无向图
            g[a].append(b)  # a 的邻居里加入 b
            g[b].append(a)  # 反向也要加：b 的邻居里加入 a
        dfs1(bob, -1, 0)  # 从 Bob 出发、父节点记为 -1、时刻 0 开始回溯
        ts[bob] = 0  # Bob 在时刻 0 位于起点 bob
        ans = -inf  # 答案先置为负无穷，后面取最大值
        dfs2(0, -1, 0, 0)  # Alice 从根 0 出发，时刻 0、初始得分 0
        return ans  # 返回所有根到叶子路径中的最大得分
