# 题目：3165. 不包含相邻元素的子序列的最大和（Maximum Sum of Subsequence With Non-adjacent Elements）
# 思路：线段树每个节点维护四个状态（左端点选/不选 × 右端点选/不选）的最大和，按「相邻元素不能同时选」合并；每次单点修改后 O(log n) 得到全区间最优。
# 时间复杂度：O(n + q log n)，建树 O(n)、每次询问 O(log n)；空间复杂度：O(n)，节点池开 4n。
def max(a: int, b: int) -> int:  # 先自定义一个两参数 max：后面合并状态时会大量调用它
    return a if a > b else b  # 返回较大的那个参数


class Node:  # 线段树节点：保存区间 [l, r] 与四种「端点选/不选」状态值
    __slots__ = "l", "r", "s00", "s01", "s10", "s11"  # 用 __slots__ 固定属性列表，省内存又比普通对象快

    def __init__(self, l: int, r: int):  # 构造函数：记录区间的左右端点
        self.l = l  # 左端点
        self.r = r  # 右端点
        self.s00 = self.s01 = self.s10 = self.s11 = 0  # 四个状态初始化为 0（空选）；第一位表示左端点是否选，第二位表示右端点是否选


class SegmentTree:  # 线段树：支持单点修改与区间查询
    __slots__ = "tr"  # 只保存节点池这一个属性

    def __init__(self, n: int):  # 构造 n 个位置的线段树
        self.tr: List[Node | None] = [None] * (n << 2)  # 4n 个槽位先全部留空；类型注解说明元素可能为 Node 或 None
        self.build(1, 1, n)  # 从根节点（编号 1，负责区间 [1, n]）开始建树

    def build(self, u: int, l: int, r: int):  # 建树：让节点 u 负责区间 [l, r]
        self.tr[u] = Node(l, r)  # 创建节点并放入节点池
        if l == r:  # 区间只剩一个位置，到了叶子
            return  # 无需分裂，直接返回
        mid = (l + r) >> 1  # 中点，(l + r) / 2 的位运算写法
        self.build(u << 1, l, mid)  # 递归建左子树 [l, mid]
        self.build(u << 1 | 1, mid + 1, r)  # 递归建右子树 [mid + 1, r]

    def query(self, u: int, l: int, r: int) -> int:  # 查询区间 [l, r] 的最优值（本题只查整个区间 [1, n]）
        if self.tr[u].l >= l and self.tr[u].r <= r:  # 节点区间被查询区间完全覆盖
            return self.tr[u].s11  # 直接返回该节点合并好的 s11
        mid = (self.tr[u].l + self.tr[u].r) >> 1  # 中点，用来判断查询区间落到哪一边
        ans = 0  # 累加器；空子序列的和为 0
        if r <= mid:  # 查询区间完全落在左半边
            ans = self.query(u << 1, l, r)  # 递归左子树
        if l > mid:  # 查询区间完全落在右半边
            ans = max(ans, self.query(u << 1 | 1, l, r))  # 与已有结果取较优（实际两个分支只会命中一个）
        return ans  # 返回区间最优值

    def pushup(self, u: int):  # 用左右子节点合并出父节点的四个状态
        left, right = self.tr[u << 1], self.tr[u << 1 | 1]  # 一次取出左右子节点，避免重复下标运算
        self.tr[u].s00 = max(left.s00 + right.s10, left.s01 + right.s00)  # 两端都不选：相邻处要么左子右端不选、要么右子左端不选，取较优
        self.tr[u].s01 = max(left.s00 + right.s11, left.s01 + right.s01)  # 左不选、右选：相邻处不能同时被选
        self.tr[u].s10 = max(left.s10 + right.s10, left.s11 + right.s00)  # 左选、右不选：同样要求相邻处不同时被选
        self.tr[u].s11 = max(left.s10 + right.s11, left.s11 + right.s01)  # 两端都选：内部相邻处仍需满足不能同时被选

    def modify(self, u: int, x: int, v: int):  # 单点修改：把位置 x 的值改成 v
        if self.tr[u].l == self.tr[u].r:  # 递归到叶子，即位置 x 本身
            self.tr[u].s11 = max(0, v)  # 叶子只有「选它」和「不选它」两种选择，取较优
            return  # 修改完成，返回上层重新合并
        mid = (self.tr[u].l + self.tr[u].r) >> 1  # 判断 x 落在当前区间的哪半边
        if x <= mid:  # 落在左半边
            self.modify(u << 1, x, v)  # 递归修改左子树
        else:  # 否则落在右半边
            self.modify(u << 1 | 1, x, v)  # 递归修改右子树
        self.pushup(u)  # 自底向上重新合并


class Solution:  # LeetCode 约定的题解类
    def maximumSumSubsequence(self, nums: List[int], queries: List[List[int]]) -> int:  # nums 为初始数组，queries 中每项是 [下标, 新值]，即一次「改值后求全区间最大和」
        n = len(nums)  # 数组长度，也是线段树区间的右端点
        tree = SegmentTree(n)  # 建树，位置编号采用 1..n
        for i, x in enumerate(nums, 1):  # 下标从 1 开始枚举，直接对上树中的位置编号
            tree.modify(1, i, x)  # 把第 i 个位置的值设为 x
        ans = 0  # 所有询问的答案之和
        mod = 10**9 + 7  # 题目要求的取模常量
        for i, x in queries:  # 依次处理每个询问：把 nums[i] 改成 x
            tree.modify(1, i + 1, x)  # 数组下标 i 对应树中位置 i + 1
            ans = (ans + tree.query(1, 1, n)) % mod  # 求当前全区间最大和，累加并取模
        return ans  # 返回累加结果
