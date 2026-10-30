# 题目：3203. 合并两棵树后的最小直径（Find Minimum Diameter After Merging Two Trees）
# 思路：先用两次 DFS 分别求出两棵树的直径 d1、d2；新直径只有三种可能——d1、d2、把两棵树各自「半径向上取整」后加一条新边，取三者最大值即可最小化。
# 时间复杂度：O(n + m)，两棵树各做两次 DFS；空间复杂度：O(n + m)，邻接表与递归栈。
class Solution:  # LeetCode 题解类，固定入口名
    def minimumDiameterAfterMerge(  # 返回合并后的最小直径；edges1、edges2 分别是两棵树的边集
        self, edges1: List[List[int]], edges2: List[List[int]]  # 参数续行：两棵树的边集（缩进续行，不属于新语句）
    ) -> int:  # 函数签名收尾
        d1 = self.treeDiameter(edges1)  # 先求第一棵树的直径
        d2 = self.treeDiameter(edges2)  # 再求第二棵树的直径
        return max(d1, d2, (d1 + 1) // 2 + (d2 + 1) // 2 + 1)  # 取三者最大值：只用第一棵、只用第二棵、或把两棵树连起来（各自半径向上取整再加新边 1）

    def treeDiameter(self, edges: List[List[int]]) -> int:  # 用两遍 DFS 求一棵树的直径（以边数计）
        def dfs(i: int, fa: int, t: int):  # 内层 DFS：从 i 出发，fa 是父结点、t 是当前深度
            for j in g[i]:  # 遍历 i 的所有邻居
                if j != fa:  # 不回头访问父结点，避免在树中绕圈
                    dfs(j, i, t + 1)  # 向子树递归，深度加一
            nonlocal ans, a  # 声明要修改外层变量 ans 与 a（闭包中必须用 nonlocal）
            if ans < t:  # 如果当前深度比已记录的最远深度更远
                ans = t  # 更新最远深度
                a = i  # 记下该最远结点，作为下一轮 DFS 的起点

        g = defaultdict(list)  # 邻接表：键是结点，值是邻接点列表（访问缺省键时自动创建空列表）
        for a, b in edges:  # 遍历每条边，双向建图
            g[a].append(b)  # 建立 a → b 的边
            g[b].append(a)  # 建立 b → a 的边
        ans = a = 0  # 初始化最远深度与最远结点（链式赋值）
        dfs(0, -1, 0)  # 第一次 DFS：从任意点 0 出发，找到直径的一个端点
        dfs(a, -1, 0)  # 第二次 DFS：从该端点出发，ans 就是直径长度
        return ans  # 返回这棵树的直径（边数）
