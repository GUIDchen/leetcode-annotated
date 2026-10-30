# 题目：1627. 带阈值的图连通性（Graph Connectivity With Threshold）
# 思路：枚举所有大于 threshold 的公因数 a，把 a 的所有倍数与 a 合并到同一个并查集，最后用根是否相同判断每个询问的连通性。
# 时间复杂度：O(n log n + q·α(n))，调和级数枚举倍数；空间复杂度：O(n)，并查集数组。
class UnionFind:  # 并查集：维护连通分量，支持合并与查询根
    def __init__(self, n):  # 构造函数：n 个元素，编号 0..n-1
        self.p = list(range(n))  # 每个元素初始自成一个集合，父节点指向自己
        self.size = [1] * n  # 每个集合的大小初始为 1，用于按大小合并

    def find(self, x):  # 路径压缩查找：返回 x 所在集合的根
        if self.p[x] != x:  # 父节点不是自己，说明还没到根
            self.p[x] = self.find(self.p[x])  # 递归找到根，并把 x 直接挂到根上
        return self.p[x]  # 返回根节点

    def union(self, a, b):  # 合并 a、b 所在集合，返回是否真的发生合并
        pa, pb = self.find(a), self.find(b)  # 先找到两个元素各自所在集合的根
        if pa == pb:  # 根相同说明本来就在同一集合
            return False  # 无需合并，返回 False
        if self.size[pa] > self.size[pb]:  # 按集合大小合并：把较小的集合挂到较大集合下面
            self.p[pb] = pa  # b 的根挂到 a 的根下
            self.size[pa] += self.size[pb]  # a 集合的大小增加
        else:  # 否则反过来挂
            self.p[pa] = pb  # a 的根挂到 b 的根下
            self.size[pb] += self.size[pa]  # b 集合的大小增加
        return True  # 合并成功，返回 True


class Solution:  # LeetCode 约定的题解类
    def areConnected(  # 方法签名折行书写：n 为编号上限，threshold 为阈值，queries 为待判断点对
        self, n: int, threshold: int, queries: List[List[int]]  # 参数列表续行，返回布尔列表
    ) -> List[bool]:  # 返回每个询问的连通性结果
        uf = UnionFind(n + 1)  # 建立 n+1 个元素的并查集（节点编号 1..n）
        for a in range(threshold + 1, n + 1):  # 枚举所有大于阈值的数 a，把它当作公因数
            for b in range(a + a, n + 1, a):  # 枚举 a 的所有倍数 b = 2a, 3a, ...
                uf.union(a, b)  # 公因数 a > threshold，说明 a 与 b 之间有边，合并两个集合
        return [uf.find(a) == uf.find(b) for a, b in queries]  # 根相同即连通，逐个询问直接算出布尔结果
