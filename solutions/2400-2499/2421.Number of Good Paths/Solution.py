# 题目：2421. 好路径的数目（Number of Good Paths）
# 核心思路：按权值从小到大把点加入并查集，只向权值不大于当前点的邻居合并；合并两个集合时新增 size[pa][v] * size[pb][v] 条以 v 为最大权值的路径。
# 时间复杂度：O(n log n + m α(n))，排序加并查集；空间复杂度：O(n + m)，邻接表与并查集结构。
class Solution:  # LeetCode 约定的题解类
    def numberOfGoodPaths(self, vals: List[int], edges: List[List[int]]) -> int:  # vals：点权；edges：无向边列表
        def find(x):  # 带路径压缩的查找
            if p[x] != x:  # 当前结点还不是根
                p[x] = find(p[x])  # 递归找到根，并把沿途结点直接挂到根上
            return p[x]  # 返回根结点

        g = defaultdict(list)  # 邻接表
        for a, b in edges:  # 遍历每条无向边
            g[a].append(b)  # 记录 a -> b
            g[b].append(a)  # 记录 b -> a，无向图需要双向

        n = len(vals)  # 结点个数
        p = list(range(n))  # 并查集父指针，初始时每个点自成集合
        size = defaultdict(Counter)  # size[根][权值] = 该集合内权值恰为该值的点数
        for i, v in enumerate(vals):  # 初始化每个单点集合
            size[i][v] = 1  # 单点集合内权值 v 的点数为 1

        ans = n  # 每条单点路径自身都是好路径，先把 n 条计入
        for v, a in sorted(zip(vals, range(n))):  # 按权值升序取出 (权值, 下标)
            for b in g[a]:  # 遍历 a 的所有邻居
                if vals[b] > v:  # 邻居权值更大，路径最大值就不是 v，不能现在合并
                    continue  # 留到处理更大的 v 时再合并
                pa, pb = find(a), find(b)  # 找到两个端点所在集合的根
                if pa != pb:  # 只有不属于同一集合才需要合并
                    ans += size[pa][v] * size[pb][v]  # 两个集合内权值为 v 的点两两配对，形成以 v 为最大值的路径
                    p[pa] = pb  # 把 pa 挂到 pb 上完成合并
                    size[pb][v] += size[pa][v]  # 合并后集合内权值为 v 的点数相加
        return ans  # 返回好路径的总数
