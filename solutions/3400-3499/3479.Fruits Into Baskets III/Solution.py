# 3479. 水果成篮 III（Fruits Into Baskets III）
# 核心思路：用线段树维护篮子容量的区间最大值，对每个水果在线段树上二分查找最左侧容量足够的篮子，占用后把该位置改成 0，找不到则计入放不下的数量。
# 复杂度：时间 O(n log n)，空间 O(n)
class SegmentTree:  # 线段树：维护篮子容量的区间最大值
    __slots__ = ["nums", "tr"]  # 限制实例属性，减少内存开销

    def __init__(self, nums):  # 构造函数，nums 为 1 起始下标的篮子容量
        self.nums = nums  # 保存原始数组
        n = len(nums)  # 篮子数量
        self.tr = [0] * (n << 2)  # 线段树节点数开到 4n
        self.build(1, 1, n)  # 建树，根节点覆盖区间 [1, n]

    def build(self, u, l, r):  # 建树：u 为节点编号，[l, r] 为其覆盖区间
        if l == r:  # 到达叶子节点
            self.tr[u] = self.nums[l - 1]  # 叶子直接取对应的篮子容量（原数组下标从 1 开始）
            return  # 返回上一层
        mid = (l + r) >> 1  # 取中点
        self.build(u << 1, l, mid)  # 递归建左子树
        self.build(u << 1 | 1, mid + 1, r)  # 递归建右子树
        self.pushup(u)  # 用左右儿子更新当前节点的最大值

    def modify(self, u, l, r, i, v):  # 单点修改：把位置 i 的容量改成 v
        if l == r:  # 到达叶子节点
            self.tr[u] = v  # 直接赋新值（篮子被占用时 v = 0）
            return  # 返回上一层
        mid = (l + r) >> 1  # 取中点
        if i <= mid:  # 目标在左半区间
            self.modify(u << 1, l, mid, i, v)  # 递归修改左子树
        else:  # 目标在右半区间
            self.modify(u << 1 | 1, mid + 1, r, i, v)  # 递归修改右子树
        self.pushup(u)  # 回溯时更新当前节点的最大值

    def query(self, u, l, r, v):  # 查询容量大于等于 v 的最左侧篮子下标，找不到返回 -1
        if self.tr[u] < v:  # 本区间最大值都不够，整段没有可用篮子
            return -1  # 直接返回 -1
        if l == r:  # 到达叶子节点
            return l  # 叶子下标即答案
        mid = (l + r) >> 1  # 取中点
        if self.tr[u << 1] >= v:  # 优先往左子树找，保证取到最左侧的合法篮子
            return self.query(u << 1, l, mid, v)  # 左子树满足条件，递归左子树
        return self.query(u << 1 | 1, mid + 1, r, v)  # 否则递归右子树

    def pushup(self, u):  # 用左右儿子的最大值更新父节点
        self.tr[u] = max(self.tr[u << 1], self.tr[u << 1 | 1])  # 节点值等于两个儿子中的较大值


class Solution:  # 解题类
    def numOfUnplacedFruits(self, fruits: List[int], baskets: List[int]) -> int:  # 返回无法放入任何篮子的水果数量
        tree = SegmentTree(baskets)  # 用篮子容量构建线段树
        n = len(baskets)  # 篮子数量
        ans = 0  # 统计放不下的水果数
        for x in fruits:  # 按顺序处理每个水果
            i = tree.query(1, 1, n, x)  # 找到容量足够的最左侧篮子
            if i < 0:  # 找不到可用的篮子
                ans += 1  # 该水果放不下，计数加一
            else:  # 找到了可用篮子
                tree.modify(1, 1, n, i, 0)  # 占用它：把该位置的容量改成 0
        return ans  # 返回放不下的水果数
