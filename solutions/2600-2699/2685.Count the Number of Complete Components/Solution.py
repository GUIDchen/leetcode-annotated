# 题目：2685. 统计完全连通分量的数量（Count the Number of Complete Components）
# 思路：先建无向邻接表，再 DFS 每个连通分量，同时统计顶点数 x 与度数之和 y；完全连通分量满足 y = x*(x-1)（每条边被两端各数一次）。
# 时间复杂度：O(n + E)，DFS 与建图各扫一遍；空间复杂度：O(n + E)，邻接表与访问数组。
class Solution:  # LeetCode 约定的题解类
    def countCompleteComponents(self, n: int, edges: List[List[int]]) -> int:  # n 是顶点数，edges 是无向边列表
        def dfs(i: int) -> (int, int):  # 递归函数：返回（分量顶点数, 分量内度数之和），g 与 vis 在调用前已准备好
            vis[i] = True  # 进入 i 时立即标记已访问，避免重复统计
            x, y = 1, len(g[i])  # x 先算 i 自己，y 先加上 i 的度数
            for j in g[i]:  # 遍历 i 的所有邻居
                if not vis[j]:  # 只递归尚未访问的邻居，保证每个顶点只统计一次
                    a, b = dfs(j)  # 递归求解邻居所在的那部分
                    x += a  # 累加顶点数
                    y += b  # 累加度数（每条边会在两端各贡献 1）
            return x, y  # 返回当前分量的顶点数与度数和

        g = defaultdict(list)  # 建无向邻接表，缺失的键会自动创建空列表
        for a, b in edges:  # 遍历每条无向边，把它加到两端点的邻接表里
            g[a].append(b)  # a 的邻居中加入 b
            g[b].append(a)  # b 的邻居中加入 a，完成双向建图
        vis = [False] * n  # vis[i] 表示顶点 i 是否已被 DFS 访问过
        ans = 0  # ans 记录完全连通分量的个数
        for i in range(n):  # 逐个起点扫描，保证每个连通分量都被处理一次
            if not vis[i]:  # 只从未访问的顶点开始新的一轮 DFS
                a, b = dfs(i)  # 拿到该连通分量的顶点数 a 与度数和 b
                ans += a * (a - 1) == b  # 布尔值可直接参与加法：y == x*(x-1) 时计数加一
        return ans  # 返回完全连通分量的数量
