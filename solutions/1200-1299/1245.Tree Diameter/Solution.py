# 题目：1245. 树的直径（Tree Diameter）
# 思路：两次 DFS —— 先任取一点求出最远点 a，再从 a 出发求最远距离，该距离就是树的直径（边数）。
# 时间复杂度：O(n)，两次遍历每条边各走一遍；空间复杂度：O(n)，邻接表与 O(n) 递归栈。
class Solution:  # LeetCode 约定的题解类
    def treeDiameter(self, edges: List[List[int]]) -> int:  # edges 是树的 n-1 条无向边，返回直径（边数）
        def dfs(i: int, fa: int, t: int):  # i 为当前点、fa 为父节点、t 为距起点的距离
            for j in g[i]:  # 枚举当前点的所有邻居
                if j != fa:  # 不回头访问父节点，避免在树上绕圈
                    dfs(j, i, t + 1)  # 递归进入子节点，距离加一
            nonlocal ans, a  # 声明要修改外层的 ans 和 a
            if ans < t:  # 后序位置：用当前深度尝试更新最远距离
                ans = t  # 记录更远的距离
                a = i  # 记录该端点，供第二次搜索作为起点

        g = defaultdict(list)  # 邻接表：节点 → 邻居列表
        for a, b in edges:  # 逐条边建图（此处 a 会在第 16 行被重新赋值）
            g[a].append(b)  # 把 b 加入 a 的邻居列表
            g[b].append(a)  # 无向边，方向反过来也要加一次
        ans = a = 0  # ans：最远距离；a：最远点编号
        dfs(0, -1, 0)  # 第一次 DFS：从任意点 0 出发，找到最远点 a
        dfs(a, -1, 0)  # 第二次 DFS：从 a 出发的最远距离就是直径
        return ans  # 返回直径（边数）
