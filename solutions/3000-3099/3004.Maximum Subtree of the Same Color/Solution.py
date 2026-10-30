# 题目：3004. 相同颜色的最大子树（Maximum Subtree of the Same Color）
# 核心思路：无向树邻接表 + 后序 DFS：dfs 返回「以当前节点为根的子树是否整体同色」，同时累计子树大小，同色时用大小更新答案。
# 时间复杂度：O(n)，每个节点只被访问一次；空间复杂度：O(n)，邻接表、size 数组与递归栈。
class Solution:  # LeetCode 约定的题解类
    def maximumSubtreeSize(self, edges: List[List[int]], colors: List[int]) -> int:  # edges 是 n-1 条无向边，colors 是每个节点的颜色
        def dfs(a: int, fa: int) -> bool:  # 内层 dfs：返回以 a 为根、父节点为 fa 的子树是否整体同色
            ok = True  # 先假设当前子树同色，出现不同色再改成 False
            for b in g[a]:  # 枚举 a 的每个邻居
                if b != fa:  # 跳过父节点，避免沿原路回走
                    t = dfs(b, a)  # 递归判断子节点 b 的子树是否同色
                    ok = ok and colors[a] == colors[b] and t  # a 与 b 同色且 b 的子树同色，a 的子树才可能仍然同色
                    size[a] += size[b]  # 子树大小逐个累加子节点的子树大小
            if ok:  # 整棵子树同色时才可能更新答案
                nonlocal ans  # 声明 ans 来自外层函数作用域，这里需要就地修改
                ans = max(ans, size[a])  # 用这棵同色子树的节点数更新最大值
            return ok  # 把同色与否回传给父节点

        n = len(edges) + 1  # 边数 + 1 就是节点数
        g = [[] for _ in range(n)]  # 邻接表，g[u] 保存与 u 直接相连的所有节点
        size = [1] * n  # size[u] 是以 u 为根的子树节点数，单个节点初始为 1
        for a, b in edges:  # 逐条边建无向图
            g[a].append(b)  # a 的邻居里加入 b
            g[b].append(a)  # b 的邻居里加入 a，两个方向都要存
        ans = 0  # ans 记录同色子树的最大节点数
        dfs(0, -1)  # 以 0 号节点为根开始 DFS，-1 表示没有父节点
        return ans  # 返回答案
