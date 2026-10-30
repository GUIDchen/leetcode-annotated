# 题目：1761. 一个图中连通三元组的最小度数（Minimum Degree of a Connected Trio in a Graph）
# 思路：邻接矩阵 + 度数数组，三重循环枚举 i<j<k，三点两两相连时用三度之和减 6 更新答案。
# 时间复杂度：O(n^3)，枚举所有三元组；空间复杂度：O(n^2)，邻接矩阵占 O(n^2)，度数数组占 O(n)。
def min(a: int, b: int) -> int:  # 自定义的二元取小函数，供下面复用
    return a if a < b else b  # a 更小返回 a，否则返回 b


class Solution:  # LeetCode 约定的题解类
    def minTrioDegree(self, n: int, edges: List[List[int]]) -> int:  # n：顶点数；edges：边列表
        g = [[False] * n for _ in range(n)]  # 邻接矩阵，g[u][v] 为 True 表示 u 与 v 相连
        deg = [0] * n  # 记录每个顶点的度数
        for u, v in edges:  # 遍历每条边
            u, v = u - 1, v - 1  # 题目编号从 1 开始，减一换算成 0 开始的下标
            g[u][v] = g[v][u] = True  # 无向图，两个方向都要标记
            deg[u] += 1  # 端点 u 的度数加一
            deg[v] += 1  # 端点 v 的度数加一
        ans = inf  # 最小度数初值为正无穷（判题环境已提供 inf）
        for i in range(n):  # 枚举三元组的第一个顶点
            for j in range(i + 1, n):  # 第二个顶点，保证下标递增避免重复
                if g[i][j]:  # i 与 j 必须相连
                    for k in range(j + 1, n):  # 第三个顶点
                        if g[i][k] and g[j][k]:  # 另外两条边都存在，构成连通三元组
                            ans = min(ans, deg[i] + deg[j] + deg[k] - 6)  # 三度之和减去组内 3 条边的 6 个度
        return -1 if ans == inf else ans  # 没有三元组返回 -1，否则返回最小度数
