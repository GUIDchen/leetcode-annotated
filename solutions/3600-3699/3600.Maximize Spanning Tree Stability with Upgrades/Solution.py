# 3600. 升级后最大生成树稳定性（Maximize Spanning Tree Stability with Upgrades）
# 核心思路：先判必选边是否成环以及原图是否连通，再对答案二分；判定用并查集优先并入原稳定性已达标（s >= lim）的边，再用至多 k 条升级可达标的边收尾，看能否连通。
# 复杂度：时间 O(m log C · α(n))，空间 O(n + m)，其中 C 为稳定性上界、α 为并查集反阿克曼函数。
class UnionFind:  # 并查集：维护连通分量与分量大小
    def __init__(self, n):  # 构造 n 个单点集合
        self.p = list(range(n))  # 父指针，初始每个节点自成一派
        self.size = [1] * n  # 每个集合初始大小为 1
        self.cnt = n  # 初始有 n 个连通分量

    def find(self, x):  # 查根，带路径压缩
        if self.p[x] != x:  # 不是根就先压缩路径
            self.p[x] = self.find(self.p[x])  # 把父指针递归挂到根上
        return self.p[x]  # 返回根节点

    def union(self, a, b):  # 合并两个集合，成功合并返回 True
        pa, pb = self.find(a), self.find(b)  # 分别求出两个端点所在集合的根
        if pa == pb:  # 已经在同一集合，无需合并
            return False  # 合并失败
        if self.size[pa] > self.size[pb]:  # 按大小合并：把小集合挂到大集合上
            self.p[pb] = pa  # pb 挂到 pa
            self.size[pa] += self.size[pb]  # 更新 pa 集合的大小
        else:  # 否则反向挂
            self.p[pa] = pb  # pa 挂到 pb
            self.size[pb] += self.size[pa]  # 更新 pb 集合的大小
        self.cnt -= 1  # 合并成功后连通分量数减一
        return True  # 合并成功


class Solution:  # 主解类
    def maxStability(self, n: int, edges: List[List[int]], k: int) -> int:  # 入口：二分求最大可行的稳定性下界
        def check(lim: int) -> bool:  # 判定能否让生成树中每条边的稳定性都 >= lim
            uf = UnionFind(n)  # 新建并查集
            for u, v, s, _ in edges:  # 第一轮：先并入不需要升级就已达标的边
                if s >= lim:  # 原稳定性已达标
                    uf.union(u, v)  # 直接并入生成树
            rem = k  # 剩余可用的升级次数
            for u, v, s, _ in edges:  # 第二轮：用升级一次即可达标的边继续连通
                if s * 2 >= lim and rem > 0:  # 升级后达标且还有升级次数
                    if uf.union(u, v):  # 这条边确实能合并两个不同的连通分量
                        rem -= 1  # 消耗一次升级次数
            return uf.cnt == 1  # 只剩一个连通分量说明所有点都能连通

        uf = UnionFind(n)  # 单独一个并查集用于必选边的合法性检查
        mn = 10**6  # 答案的上界：必选边稳定性的最小值
        for u, v, s, must in edges:  # 先处理必选边
            if must:  # 是必选边
                mn = min(mn, s)  # 答案不会超过必选边中的最小稳定性
                if not uf.union(u, v):  # 必选边导致成环
                    return -1  # 无法构成合法生成树
        for u, v, _, _ in edges:  # 再用全部边检查整张图的连通性
            uf.union(u, v)  # 合并该边的两个端点
        if uf.cnt > 1:  # 原图本身就不连通
            return -1  # 不存在生成树，返回 -1
        l, r = 1, mn  # 二分区间：答案在 [1, mn] 内
        while l < r:  # 找最大的可行值
            mid = (l + r + 1) >> 1  # 上取整的中点，避免死循环
            if check(mid):  # mid 可行
                l = mid  # 尝试更大的下界
            else:  # mid 不可行
                r = mid - 1  # 缩小上界
        return l  # l 即最大可行的稳定性
