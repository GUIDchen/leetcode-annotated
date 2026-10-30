# 题目：3108. 带权图里旅途的最小代价（Minimum Cost Walk in Weighted Graph）
# 思路：并查集求出连通分量，把同一分量内所有边权按位与起来（分量内可以反复绕行，路径代价就是这些边的与）；查询时同点返回 0、同分量返回与值、否则 -1。
# 时间复杂度：O((V + E + Q) α(V))，并查集近似常数；空间复杂度：O(V)，存父数组、大小数组与分量代价。
class UnionFind:  # 并查集：维护连通分量，支持按大小合并与路径压缩
    def __init__(self, n):  # 构造：n 个结点，初始各自成一个集合
        self.p = list(range(n))  # p[i] 表示 i 的父结点，初始指向自己
        self.size = [1] * n  # size[i] 只在 i 是根时有效，表示集合大小

    def find(self, x):  # 查找 x 所在集合的根，同时做路径压缩
        if self.p[x] != x:  # x 还不是根
            self.p[x] = self.find(self.p[x])  # 递归找到根，并把 x 直接挂到根上
        return self.p[x]  # 返回根结点

    def union(self, a, b):  # 合并 a、b 所在集合，返回是否真的发生了合并
        pa, pb = self.find(a), self.find(b)  # 分别找到两个根
        if pa == pb:  # 本来就在同一集合
            return False  # 不需要合并
        if self.size[pa] > self.size[pb]:  # 小树挂大树，控制树高
            self.p[pb] = pa  # b 的根改为指向 a 的根
            self.size[pa] += self.size[pb]  # 新根大小要加上被并入的集合
        else:  # 否则让 pa 挂到 pb 上
            self.p[pa] = pb  # a 的根改为指向 b 的根
            self.size[pb] += self.size[pa]  # 更新新根的大小
        return True  # 合并成功


class Solution:  # LeetCode 约定的题解类
    def minimumCost(  # 返回每个查询的最小代价列表
        self, n: int, edges: List[List[int]], query: List[List[int]]  # n：点数；edges：带权边；query：查询对
    ) -> List[int]:  # 返回值是每个查询的答案
        g = [-1] * n  # g[root] 存该分量内所有边权的按位与，-1 是全 1 掩码
        uf = UnionFind(n)  # 建立并查集
        for u, v, _ in edges:  # 第一遍：合并每条边的两个端点
            uf.union(u, v)  # 合并出连通分量
        for u, _, w in edges:  # 第二遍：把边权按位与到所属分量
            root = uf.find(u)  # 该边所属连通分量的根
            g[root] &= w  # 反复与运算，得到该分量的最小可走代价

        def f(u: int, v: int) -> int:  # 辅助函数：返回 u 到 v 的最小代价
            if u == v:  # 起点就是终点
                return 0  # 不用走边，代价为 0
            a, b = uf.find(u), uf.find(v)  # 分别求两个端点的根
            return g[a] if a == b else -1  # 同分量返回与值，否则返回 -1

        return [f(s, t) for s, t in query]  # 对每个查询求值并汇总成列表
