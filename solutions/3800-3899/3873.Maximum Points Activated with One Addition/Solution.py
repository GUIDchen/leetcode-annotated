# 3873. 添加一个点后可激活的最大点数（Maximum Points Activated with One Addition）
# 核心思路：把点 (x, y) 看成边 x -- (y + 大偏移) 做并查集合并，连通分量即一条线上互相可达的点集；若加一个点，可以把两个分量连起来，答案是最大分量 + 次大分量 + 1。
# 复杂度：时间复杂度 O(n·α(n))，空间复杂度 O(n)。
class UnionFind:  # 并查集类
    def __init__(self):  # 构造函数
        self.p = {}  # 父指针表（懒初始化）
        self.size = {}  # 每个集合的大小

    def find(self, x):  # 查找 x 所在集合的根
        if x not in self.p:  # x 第一次出现
            self.p[x] = x  # 自己是自己的父节点
            self.size[x] = 1  # 集合大小初始为 1
        if self.p[x] != x:  # x 不是根节点
            self.p[x] = self.find(self.p[x])  # 路径压缩，把根直接挂成父节点
        return self.p[x]  # 返回根节点

    def union(self, a, b):  # 合并 a、b 两个集合
        pa, pb = self.find(a), self.find(b)  # 分别求出两个集合的根
        if pa == pb:  # 已经同属一个集合
            return False  # 无需合并
        if self.size[pa] > self.size[pb]:  # 按大小合并：pa 更大
            self.p[pb] = pa  # 小集合挂到大集合上
            self.size[pa] += self.size[pb]  # 更新大集合大小
        else:  # pb 不小于 pa
            self.p[pa] = pb  # 把 pa 挂到 pb 上
            self.size[pb] += self.size[pa]  # 更新 pb 的大小
        return True  # 合并成功


class Solution:  # 题解类
    def maxActivated(self, points: List[List[int]]) -> int:  # 返回添加一个点后能激活的最大点数
        uf = UnionFind()  # 建立并查集
        m = int(3e9)  # 大偏移量，把 y 坐标平移到与 x 坐标不重叠的取值区间

        for x, y in points:  # 遍历每个点
            uf.union(x, y + m)  # 把横坐标与「平移后的纵坐标」连成一条边

        cnt = Counter()  # 统计每个连通分量包含的点数
        for x, _ in points:  # 再次遍历每个点
            cnt[uf.find(x)] += 1  # 该点所属分量计数加一

        mx1 = mx2 = 0  # mx1 为最大分量，mx2 为次大分量
        for x in cnt.values():  # 遍历所有分量大小
            if mx1 < x:  # 出现新的最大分量
                mx2 = mx1  # 原最大值降为次大值
                mx1 = x  # 更新最大值
            elif mx2 < x:  # 没超过最大值但超过次大值
                mx2 = x  # 更新次大值
        return mx1 + mx2 + 1  # 新增点把两个最大分量连起来，再加上新增点本身
