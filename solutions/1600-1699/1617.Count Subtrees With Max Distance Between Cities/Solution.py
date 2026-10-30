# 题目：1617. 统计子树中城市之间最大距离（Count Subtrees With Max Distance Between Cities）
# 思路：枚举点集位掩码，两次 DFS 求直径：第一次从集合内某点找最远点，第二次从该点求最远距离；msk 被清空则说明该子集连通。
# 时间复杂度：O(2^n * n)，每个子集做两次 O(n) 的 DFS；空间复杂度：O(n + m)，邻接表与递归栈。
class Solution:  # LeetCode 约定的题解类
    def countSubgraphsForEachDiameter(  # 返回长度为 n-1 的数组，第 d-1 项是直径为 d 的子树个数
        self, n: int, edges: List[List[int]]  # n：城市数；edges：树的边，编号从 1 开始
    ) -> List[int]:  # 返回结果列表的签名结束
        def dfs(u: int, d: int = 0):  # 从 u 出发在 msk 限定的点集内深搜，d 为已走距离
            nonlocal mx, nxt, msk  # 声明要修改外层函数里的三个变量
            if mx < d:  # 走到更远的点，更新最远距离
                mx, nxt = d, u  # 同时记录新的最大距离与对应的最远点
            msk ^= 1 << u  # 异或把 u 从「未访问」集合中抹掉，即标记为已访问
            for v in g[u]:  # 考察 u 的所有邻居
                if msk >> v & 1:  # 只走仍在点集内且尚未访问的点，避免越出子集或重复
                    dfs(v, d + 1)  # 继续深入，距离加一

        g = defaultdict(list)  # 邻接表：缺省值 list，省去手动建空列表的步骤
        for u, v in edges:  # 遍历每条边
            u, v = u - 1, v - 1  # 题目编号从 1 开始，统一转成 0 基
            g[u].append(v)  # 记录 u → v 的边
            g[v].append(u)  # 记录 v → u 的边
        ans = [0] * (n - 1)  # ans[d-1] 表示直径为 d 的子树个数，直径最大为 n-1
        nxt = mx = 0  # nxt：当前最远点；mx：当前最远距离
        for mask in range(1, 1 << n):  # 枚举所有非空的点子集
            if mask & (mask - 1) == 0:  # 去掉最低位后为 0，说明只有一个点，没有距离
                continue  # 跳过单点集
            msk, mx = mask, 0  # 还原待访问集合：只有 mask 里的点能被走到；同时重置最远距离
            cur = msk.bit_length() - 1  # 取 mask 的最高位下标作为 DFS 起点
            dfs(cur)  # 第一次 DFS：找到集合内距离起点最远的点 nxt
            if msk == 0:  # 所有点都被走到，说明子集连通，才可能构成子树
                msk, mx = mask, 0  # 重新初始化访问标记与最远距离
                dfs(nxt)  # 第二次 DFS：从 nxt 出发，最远距离就是这棵子树的直径
                ans[mx - 1] += 1  # 按直径归类计数（直径至少为 1，因此下标要减一）
        return ans  # 返回每种直径对应的子树个数
