# 题目：1489. 找到最小生成树里的关键边和伪关键边（Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree）
# 核心思路：先排序求基准 MST 权值 v；再对每条边分别「禁用后重跑」「强制选中后重跑」Kruskal，据权值变化判定其角色。
# 时间复杂度：O(E^2 α(n) + E log E)；空间复杂度：O(n + E)。
class UnionFind:  # 并查集：维护连通分量，供 Kruskal 判定成环
    def __init__(self, n):  # n 为节点数
        self.p = list(range(n))  # 父数组，初始每个节点自成一个分量
        self.n = n  # 当前连通分量个数

    def union(self, a, b):  # 合并 a、b 所在分量，成功说明该边被选入 MST
        if self.find(a) == self.find(b):  # 已在同一分量，合并会成环
            return False  # 返回 False 表示这条边没有并入任何新节点
        self.p[self.find(a)] = self.find(b)  # 把 a 的根挂到 b 的根下
        self.n -= 1  # 分量数减一
        return True  # 返回合并成功

    def find(self, x):  # 查根，带路径压缩
        if self.p[x] != x:  # 当前节点不是根
            self.p[x] = self.find(self.p[x])  # 递归找到根，并把沿途节点直接挂到根上
        return self.p[x]  # 返回根节点


class Solution:  # LeetCode 约定的题解类
    def findCriticalAndPseudoCriticalEdges(  # 返回 [关键边下标列表, 伪关键边下标列表]
        self, n: int, edges: List[List[int]]
    ) -> List[List[int]]:  # n 为节点数，edges 为 {u, v, w} 边列表
        for i, e in enumerate(edges):  # 遍历每条边
            e.append(i)  # 追加原始下标，排序后仍能定位这条边
        edges.sort(key=lambda x: x[2])  # 按边权升序排序，供 Kruskal 使用
        uf = UnionFind(n)  # 基准并查集
        v = sum(w for f, t, w, _ in edges if uf.union(f, t))  # 跑一遍 Kruskal，累加得到的 MST 权值和 v
        ans = [[], []]  # ans[0] 存关键边，ans[1] 存伪关键边
        for f, t, w, i in edges:  # 逐条边判断它在 MST 中的角色
            uf = UnionFind(n)  # 场景一：禁用当前边后重建 MST
            k = sum(z for x, y, z, j in edges if j != i and uf.union(x, y))  # 跳过该边跑 Kruskal 并累加权值
            if uf.n > 1 or (uf.n == 1 and k > v):  # 图不连通或权值变大，说明该边不可替代
                ans[0].append(i)  # 记入关键边
                continue  # 关键边不再参与伪关键边判定

            uf = UnionFind(n)  # 场景二：强制选中当前边
            uf.union(f, t)  # 先合并该边两端点
            k = w + sum(z for x, y, z, j in edges if j != i and uf.union(x, y))  # 以该边为起点继续 Kruskal，累加剩余权值
            if k == v:  # 仍能取得最小权值和
                ans[1].append(i)  # 说明它是伪关键边
        return ans  # 返回 [关键边, 伪关键边] 两个列表
