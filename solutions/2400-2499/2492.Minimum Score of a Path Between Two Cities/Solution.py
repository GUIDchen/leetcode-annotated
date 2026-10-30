# 题目：2492. 两个城市间路径的最小分数（Minimum Score of a Path Between Two Cities）
# 思路：从城市 1 出发 DFS 整个连通块，路径分数取经过边的最小权值，答案就是该连通块内所有边权的最小值。
# 时间复杂度：O(n + m)，每个点与每条边各访问常数次；空间复杂度：O(n + m)，邻接表、访问数组与递归栈。
class Solution:  # LeetCode 约定的题解类
    def minScore(self, n: int, roads: List[List[int]]) -> int:  # n 是城市数（编号 1..n），roads 是无向带权边 [a, b, w]
        def dfs(a: int):  # 内层 DFS：遍历 a 所在连通块，顺带更新最小边权 ans
            vis[a] = True  # 标记当前点已访问，避免重复递归
            nonlocal ans  # 声明 ans 来自外层函数，才能在闭包里修改它
            for b, w in g[a]:  # 遍历与 a 相邻的每条边，取出邻点 b 与权值 w
                ans = min(ans, w)  # 路径分数取经过边的最小权值，逐边更新
                if not vis[b]:  # 只有未访问过的邻点才继续深入
                    dfs(b)  # 递归访问邻点

        g = [[] for _ in range(n + 1)]  # 邻接表，下标 1..n，每项存 (邻点, 权值)
        for a, b, w in roads:  # 把每条无向边拆成双向边建图
            g[a].append((b, w))  # a 到 b 存一条权值为 w 的边
            g[b].append((a, w))  # b 到 a 再存一条，构成无向图
        ans = inf  # 最小边权，初始为无穷大
        vis = [False] * (n + 1)  # 访问标记数组，下标 0..n
        dfs(1)  # 从城市 1 出发覆盖它所在连通块
        return ans  # 连通块内最小边权即答案（1 与 n 保证连通）
