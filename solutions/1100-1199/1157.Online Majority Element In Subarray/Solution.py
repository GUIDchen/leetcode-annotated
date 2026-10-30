# 题目：1157. 子数组中占绝大多数的元素（Online Majority Element In Subarray）
# 思路：线段树维护区间的 Boyer-Moore 候选值与票数，再用「值 → 下标列表」二分确认出现次数。
# 时间复杂度：建树 O(n)，每次查询 O(log n)；空间复杂度：O(n)。
class Node:  # 线段树节点
    __slots__ = ("l", "r", "x", "cnt")  # 用 __slots__ 省内存，只允许这四个属性

    def __init__(self):  # 初始化节点
        self.l = self.r = 0  # l、r：该节点负责的区间左右端点
        self.x = self.cnt = 0  # x：Boyer-Moore 候选值；cnt：抵消后剩余的票数


class SegmentTree:  # 维护区间「候选值 + 票数」的线段树
    def __init__(self, nums):  # 构造：nums 为原始数组
        self.nums = nums  # 存下原数组，供建树时取值
        n = len(nums)  # 数组长度
        self.tr = [Node() for _ in range(n << 2)]  # 开 4n 个节点，足够覆盖线段树
        self.build(1, 1, n)  # 从根节点建树，区间用 1..n 表示

    def build(self, u, l, r):  # 递归建树：节点 u 对应区间 [l, r]
        self.tr[u].l, self.tr[u].r = l, r  # 记录该节点的区间
        if l == r:  # 到达叶子节点
            self.tr[u].x = self.nums[l - 1]  # 叶子值（数组下标 0 基，所以减 1）
            self.tr[u].cnt = 1  # 单个元素的票数为 1
            return  # 叶子建完直接返回
        mid = (l + r) >> 1  # 区间中点
        self.build(u << 1, l, mid)  # 递归建左子树
        self.build(u << 1 | 1, mid + 1, r)  # 递归建右子树
        self.pushup(u)  # 用两个孩子合并出当前节点

    def query(self, u, l, r):  # 查询区间 [l, r] 的候选值与票数
        if self.tr[u].l >= l and self.tr[u].r <= r:  # 节点区间被查询区间完全覆盖
            return self.tr[u].x, self.tr[u].cnt  # 直接返回该节点保存的结果
        mid = (self.tr[u].l + self.tr[u].r) >> 1  # 当前节点区间的中点
        if r <= mid:  # 查询完全落在左子树
            return self.query(u << 1, l, r)  # 递归查询左子树
        if l > mid:  # 查询完全落在右子树
            return self.query(u << 1 | 1, l, r)  # 递归查询右子树
        x1, cnt1 = self.query(u << 1, l, r)  # 查询左半部分的结果
        x2, cnt2 = self.query(u << 1 | 1, l, r)  # 查询右半部分的结果
        if x1 == x2:  # 两侧候选值相同，票数相加
            return x1, cnt1 + cnt2  # 合并后的结果
        if cnt1 >= cnt2:  # 左侧票数不少于右侧
            return x1, cnt1 - cnt2  # 票数相减，候选值仍取左侧
        else:  # 右侧票数更多
            return x2, cnt2 - cnt1  # 票数相减，候选值取右侧

    def pushup(self, u):  # 用左右孩子合并出节点 u
        if self.tr[u << 1].x == self.tr[u << 1 | 1].x:  # 左右候选值相同
            self.tr[u].x = self.tr[u << 1].x  # 候选值保持不变
            self.tr[u].cnt = self.tr[u << 1].cnt + self.tr[u << 1 | 1].cnt  # 票数相加
        elif self.tr[u << 1].cnt >= self.tr[u << 1 | 1].cnt:  # 左侧票数不少于右侧
            self.tr[u].x = self.tr[u << 1].x  # 候选值取左侧
            self.tr[u].cnt = self.tr[u << 1].cnt - self.tr[u << 1 | 1].cnt  # 票数相减
        else:  # 右侧票数更多
            self.tr[u].x = self.tr[u << 1 | 1].x  # 候选值取右侧
            self.tr[u].cnt = self.tr[u << 1 | 1].cnt - self.tr[u << 1].cnt  # 票数相减


class MajorityChecker:  # 题目要求的查询类
    def __init__(self, arr: List[int]):  # 构造：建线段树，并记录每个值的所有下标
        self.tree = SegmentTree(arr)  # 建线段树，用于取区间候选值
        self.d = defaultdict(list)  # 值 → 出现下标列表（升序）
        for i, x in enumerate(arr):  # 遍历数组
            self.d[x].append(i)  # 记录 x 出现的下标

    def query(self, left: int, right: int, threshold: int) -> int:  # 查询 [left, right] 中出现次数不少于 threshold 的值
        x, _ = self.tree.query(1, left + 1, right + 1)  # 线段树取候选值（内部区间 1 基，故加 1）
        l = bisect_left(self.d[x], left)  # 候选值在查询区间内的首个下标
        r = bisect_left(self.d[x], right + 1)  # 查询区间右端之后的首个下标
        return x if r - l >= threshold else -1  # 出现次数达标返回候选值，否则返回 -1


# Your MajorityChecker object will be instantiated and called as such:
# obj = MajorityChecker(arr)
# param_1 = obj.query(left,right,threshold)
