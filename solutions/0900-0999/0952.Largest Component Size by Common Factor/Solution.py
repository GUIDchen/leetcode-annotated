# 题目：952. 按公因数计算最大组件大小（Largest Component Size by Common Factor）
# 思路：把每个数与其因子在并查集中合并；最后统计每个根下原数组元素的个数，取最大值。
# 时间复杂度：O(n·√M·α)，M 为最大数值；空间复杂度：O(M)，父指针数组与最大数值同阶。
class UnionFind:  # 并查集：维护「数值 / 因子」之间的连通关系
    def __init__(self, n):  # n：节点个数（最大数值 + 1）
        self.p = list(range(n))  # 父指针数组，节点编号就是数值，初始各自成集合

    def union(self, a, b):  # 合并 a、b 所在集合（这里不按集合大小合并）
        pa, pb = self.find(a), self.find(b)  # 分别求出两个节点所在集合的根
        if pa != pb:  # 根不同说明还没连通
            self.p[pa] = pb  # 让 pa 指向 pb，完成一次合并

    def find(self, x):  # 查找 x 的根，并做路径压缩
        if self.p[x] != x:  # 父指针不是自己，说明还没直接指向根
            self.p[x] = self.find(self.p[x])  # 递归找根，并把路径上的节点挂到根上
        return self.p[x]  # 返回根节点


class Solution:  # 题解主类
    def largestComponentSize(self, nums: List[int]) -> int:  # nums 是待分组的一组正整数
        uf = UnionFind(max(nums) + 1)  # 节点 0..max(nums) 覆盖所有可能出现的数值与因子
        for v in nums:  # 逐个处理数组中的每个数
            i = 2  # 因子从 2 开始枚举，1 不能作为连通依据
            while i <= v // i:  # 只枚举到 sqrt(v)，用整除形式避免浮点误差
                if v % i == 0:  # 找到一个因子 i
                    uf.union(v, i)  # 把数 v 与因子 i 合并
                    uf.union(v, v // i)  # 同时把配对的另一个因子 v // i 也合并
                i += 1  # 因子试探前进一位
        return max(Counter(uf.find(v) for v in nums).values())  # 统计每个根下的元素个数（Counter），取最大组件大小
