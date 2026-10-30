# 题目：2925. 在树上执行操作以后得到的最大分数（Maximum Score After Applying Operations on a Tree）
# 思路：树形 DP。dfs 返回 (a, b)：a 是子树内不做任何操作时的总分（子树所有值之和，必然健康），b 是子树内可执行操作且根到每条叶子的路径仍保留至少一个非零值时的最大得分。
# 时间复杂度：O(n)，每个节点只被访问一次；空间复杂度：O(n)，邻接表加递归栈。
class Solution:  # LeetCode 约定的题解类
    def maximumScoreAfterOperations(
        self, edges: List[List[int]], values: List[int]
    ) -> int:  # edges：树的边；values：每个节点的值
        def dfs(i: int, fa: int = -1) -> (int, int):  # fa 是父节点，避免走回头路；返回 (a, b)
            a = b = 0  # a 累加孩子的 a（子树总和），b 累加孩子的 b（健康约束下的最优分）
            leaf = True  # 先假定 i 是叶子，遇到孩子再翻转
            for j in g[i]:  # 遍历 i 的所有邻居
                if j != fa:  # 只往儿子方向递归
                    leaf = False  # 存在儿子，说明 i 不是叶子
                    aa, bb = dfs(j, i)  # 递归求出孩子 j 的两种状态
                    a += aa  # 汇总孩子子树的全部值
                    b += bb  # 汇总孩子在健康约束下能拿到的最大分
            if leaf:  # 叶子不能被执行操作，否则根到它的路径和会变成 0
                return values[i], 0  # 不操作时贡献自身值；操作则非法，记 0
            return values[i] + a, max(values[i] + b, a)  # 不操作 i 时自身值保留、儿子可全清空；操作 i 时得自身值、儿子须各自健康，取较大者

        g = [[] for _ in range(len(values))]  # 邻接表，每个节点对应一个列表
        for a, b in edges:  # 逐条处理无向边
            g[a].append(b)  # a 的邻居加入 b
            g[b].append(a)  # b 的邻居加入 a
        return dfs(0)[1]  # 从根 0 开始，取 b（整棵子树必须健康）
