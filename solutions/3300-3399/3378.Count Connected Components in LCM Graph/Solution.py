# 题目：3378. 统计最小公倍数图中的连通块数目（Count Connected Components in LCM Graph）
# 思路：两点连边等价于存在 g ≤ threshold 同时整除两者。用并查集把每个 num 与它不超过 threshold 的所有倍数合并，最后统计不同代表（> threshold 的数自成一块）的个数。
# 时间复杂度：O((n + threshold) · log threshold · α)；空间复杂度：O(threshold)。
class DSU:  # 并查集：维护「最小公倍数 ≤ threshold」的连通关系
    def __init__(self, n):  # 构造函数：n 通常传入 threshold + 1，保证集合覆盖 0..threshold
        self.parent = {i: i for i in range(n)}  # parent：父节点字典，初始时每个点的父节点是自己
        self.rank = {i: 0 for i in range(n)}  # rank：秩字典，初始都为 0

    def make_set(self, v):  # 单独建一个集合（本解法未调用，保留并查集模板接口）
        self.parent[v] = v  # 父节点指向自己
        self.rank[v] = 1  # 秩置为 1

    def find(self, x):  # 查根，并做路径压缩
        if self.parent[x] != x:  # 自己不是根，需要继续往上找
            self.parent[x] = self.find(self.parent[x])  # 递归找到根后把 x 的父节点直接改成根，压缩路径
        return self.parent[x]  # 返回根节点

    def union_set(self, u, v):  # 合并 u、v 所在的两个集合
        u = self.find(u)  # 先找到 u 的根
        v = self.find(v)  # 再找到 v 的根
        if u != v:  # 根不同才需要真正合并
            if self.rank[u] < self.rank[v]:  # 保证 u 是秩较大的根，减少树高
                u, v = v, u  # 交换，使 u 始终是秩较大的那个
            self.parent[v] = u  # 把秩小的树挂到秩大的树下
            if self.rank[u] == self.rank[v]:  # 两棵树的秩相同，合并后高度会加一
                self.rank[u] += 1  # 秩加一


class Solution:  # LeetCode 约定的题解类
    def countComponents(self, nums, threshold):  # nums：图中的数字；threshold：允许的最小公倍数上界
        dsu = DSU(threshold + 1)  # 用 0..threshold 建并查集

        for num in nums:  # 枚举每个给定数字
            for j in range(num, threshold + 1, num):  # 枚举 num 的所有倍数 j（含 num 自己，且不超过 threshold）
                dsu.union_set(num, j)  # lcm(num, j) = j ≤ threshold，所以二者必须属于同一连通块

        unique_parents = set()  # 用集合统计每个连通块的代表，自动去重
        for num in nums:  # 再遍历一次所有数字
            if num > threshold:  # 大于 threshold 的数不可能与任何数构成合法 lcm
                unique_parents.add(num)  # 因此它自成一块，直接把自己作为代表
            else:  # 否则它已经并入某个集合
                unique_parents.add(dsu.find(num))  # 取它所在集合的根作为代表

        return len(unique_parents)  # 不同代表的个数就是连通块数目
