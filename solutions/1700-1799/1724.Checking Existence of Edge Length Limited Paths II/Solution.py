# 题目：1724. 检查边长度限制的路径是否存在 II（Checking Existence of Edge Length Limited Paths II）难度：困难
# 思路：把所有边按权值升序依次加入“持久化并查集”，每次合并时记下合并发生的时刻（边权），只按秩合并且不路径压缩，
# 于是历史版本不会被破坏；查询时 find(x, limit) 只沿“合并时刻 < limit”的父边向上走，两边落在同一根即说明存在只含小于 limit 的路径。
# 时间复杂度：构造 O(m log m + m log n)，单次查询 O(log n)；空间复杂度：O(n)，三个长度为 n 的数组。
class PersistentUnionFind:  # 持久化并查集：可按“时刻 t”回溯到历史状态
    def __init__(self, n):  # n：节点个数
        self.rank = [0] * n  # 每个集合的秩（树的近似高度），用于按秩合并
        self.p = list(range(n))  # 父节点数组，初始时每个节点自成一个集合
        self.version = [inf] * n  # version[x]：x 被挂到新父节点上的时刻（边权），初始为无穷大

    def find(self, x, t=inf):  # 在“时刻 t”的版本下查找 x 的根
        if self.p[x] == x or self.version[x] >= t:  # 已是根，或挂父节点的时刻晚于 t（该边还没加入）
            return x  # 那么 x 自己就是当前版本下的根
        return self.find(self.p[x], t)  # 否则继续沿父指针向上查找（不压缩路径，保留历史）

    def union(self, a, b, t):  # 在时刻 t 合并 a、b 所在集合
        pa, pb = self.find(a), self.find(b)  # 取 a、b 在最新版本下的根
        if pa == pb:  # 已经在同一个集合里
            return False  # 无需合并，返回 False 表示这条边被忽略
        if self.rank[pa] > self.rank[pb]:  # 按秩合并：把矮树挂到高树下
            self.version[pb] = t  # 记录 b 的根挂到 a 的根上的时刻
            self.p[pb] = pa  # 修改父指针完成合并
        else:  # 反之把 a 的根挂到 b 的根下
            self.version[pa] = t  # 记录 a 的根挂到 b 的根上的时刻
            self.p[pa] = pb  # 修改父指针完成合并
            if self.rank[pa] == self.rank[pb]:  # 两棵树等高
                self.rank[pb] += 1  # 合并后高度加一，维持按秩合并的正确性
        return True  # 合并成功


class DistanceLimitedPathsExist:  # 题面要求实现的类
    def __init__(self, n: int, edgeList: List[List[int]]):  # n：节点数；edgeList：边三元组 (u, v, dis)
        self.puf = PersistentUnionFind(n)  # 用节点数初始化持久化并查集
        edgeList.sort(key=lambda x: x[2])  # 把边按权值升序排序
        for u, v, dis in edgeList:  # 按权值从小到大依次加边
            self.puf.union(u, v, dis)  # 用边权作为合并时刻，合并这条边的两个端点

    def query(self, p: int, q: int, limit: int) -> bool:  # p、q：起终点；limit：路径上每条边都必须严格小于它
        return self.puf.find(p, limit) == self.puf.find(q, limit)  # 只看 limit 之前合并的边，同根即存在合法路径
