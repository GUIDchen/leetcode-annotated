# 题目：2569. 更新数组后处理求和查询（Handling Sum Queries After Update）
# 思路：type 1 是 nums1 的区间 0/1 翻转，用带懒标记的线段树维护区间内 1 的个数；type 2 使 nums2 总和增加 p ×（nums1 中 1 的个数）；type 3 直接输出当前总和。
# 时间复杂度：O((n + q) log n)，每次翻转/查询都是区间操作；空间复杂度：O(n)，线段树开 4n 个节点。
class Node:  # 线段树节点
    def __init__(self):  # 初始化一个空节点
        self.l = self.r = 0  # 该节点负责的闭区间 [l, r]
        self.s = self.lazy = 0  # s：区间内 1 的个数；lazy：待下传的翻转标记


class SegmentTree:  # 支持「区间 0/1 翻转」与「区间和查询」的懒标记线段树
    def __init__(self, nums):  # 用初始数组建树
        self.nums = nums  # 保存数组引用，build 建叶子时按下标取值
        n = len(nums)  # 元素个数
        self.tr = [Node() for _ in range(n << 2)]  # 预先分配 4n 个节点（n << 2 即 4n），保证不会越界
        self.build(1, 1, n)  # 从 1 号节点开始递归建树，区间下标采用 1 ~ n 的写法

    def build(self, u, l, r):  # 以 u 为根，建立负责区间 [l, r] 的子树
        self.tr[u].l, self.tr[u].r = l, r  # 记录该节点负责的左右端点
        if l == r:  # 递归到叶子节点
            self.tr[u].s = self.nums[l - 1]  # 叶子只代表一个元素，和等于该元素本身（树下标 1 对应数组下标 0）
            return  # 叶子无需继续分裂
        mid = (l + r) >> 1  # 区间中点
        self.build(u << 1, l, mid)  # 递归建立左子树 [l, mid]
        self.build(u << 1 | 1, mid + 1, r)  # 递归建立右子树 [mid+1, r]
        self.pushup(u)  # 左右子树建好后，用它们的和算出当前节点的和

    def modify(self, u, l, r):  # 把区间 [l, r] 里的每个数原地翻转（0 变 1、1 变 0）
        if self.tr[u].l >= l and self.tr[u].r <= r:  # 当前节点区间被目标区间完全覆盖
            self.tr[u].lazy ^= 1  # 打上翻转标记，等需要时再下传给子节点
            self.tr[u].s = self.tr[u].r - self.tr[u].l + 1 - self.tr[u].s  # 整段翻转后 1 的个数变成「长度 - 原来的个数」
            return  # 完全覆盖就不必再往下递归
        self.pushdown(u)  # 没有完全覆盖，先把本节点积累的标记下传给子节点
        mid = (self.tr[u].l + self.tr[u].r) >> 1  # 当前区间的中点，用来判断左右子节点
        if l <= mid:  # 目标区间与左子区间有交集
            self.modify(u << 1, l, r)  # 递归处理左子节点（u << 1 即 2u）
        if r > mid:  # 目标区间与右子区间有交集
            self.modify(u << 1 | 1, l, r)  # 递归处理右子节点（u << 1 | 1 即 2u+1）
        self.pushup(u)  # 子节点更新完毕，用它们的和修正当前节点

    def query(self, u, l, r):  # 查询区间 [l, r] 内 1 的个数
        if self.tr[u].l >= l and self.tr[u].r <= r:  # 当前节点区间被查询区间完全覆盖
            return self.tr[u].s  # 直接返回该节点维护的和
        self.pushdown(u)  # 需要下钻子节点，先保证子节点的信息是最新的
        mid = (self.tr[u].l + self.tr[u].r) >> 1  # 当前区间的中点
        res = 0  # 累计答案
        if l <= mid:  # 左子区间有重叠部分
            res += self.query(u << 1, l, r)  # 累加左子区间的结果
        if r > mid:  # 右子区间有重叠部分
            res += self.query(u << 1 | 1, l, r)  # 累加右子区间的结果
        return res  # 返回区间总和

    def pushup(self, u):  # 由子节点信息更新父节点
        self.tr[u].s = self.tr[u << 1].s + self.tr[u << 1 | 1].s  # 父区间 1 的个数等于左右子区间之和

    def pushdown(self, u):  # 把父节点的翻转标记下传给两个子节点
        if self.tr[u].lazy:  # 只有存在待下传的翻转标记时才需要处理
            mid = (self.tr[u].l + self.tr[u].r) >> 1  # 中点，用来计算左右子区间的长度
            self.tr[u << 1].s = mid - self.tr[u].l + 1 - self.tr[u << 1].s  # 左子节点整段翻转：1 的个数变成 长度 - 原个数
            self.tr[u << 1].lazy ^= 1  # 左子节点累积一次翻转标记（两次翻转互相抵消，所以用异或）
            self.tr[u << 1 | 1].s = self.tr[u].r - mid - self.tr[u << 1 | 1].s  # 右子节点整段翻转：同样用「长度 - 原个数」
            self.tr[u << 1 | 1].lazy ^= 1  # 右子节点累积一次翻转标记
            self.tr[u].lazy ^= 1  # 标记已下传，清空当前节点的懒标记


class Solution:  # LeetCode 约定的题解类
    def handleQuery(  # nums1、nums2 是初始数组，queries 是三类操作
        self, nums1: List[int], nums2: List[int], queries: List[List[int]]  # 三个参数分别是两个数组与查询列表
    ) -> List[int]:  # 返回所有 type 3 查询的答案
        tree = SegmentTree(nums1)  # 只对 nums1 建线段树，因为只有它会被区间翻转
        s = sum(nums2)  # 维护 nums2 当前的元素总和
        ans = []  # 保存所有 type 3 查询的回答
        for op, a, b in queries:  # 按顺序处理每条查询，拆出操作类型与前两个参数
            if op == 1:  # type 1：翻转 nums1 的下标区间 [a, b]
                tree.modify(1, a + 1, b + 1)  # 树中下标从 1 开始，所以左右端点都加 1
            elif op == 2:  # type 2：nums2 的每个元素都加上 a ×（nums1 中 1 的个数）
                s += a * tree.query(1, 1, len(nums1))  # 总和增加 a × 1 的个数（Python 整数不会溢出，无需转型）
            else:  # type 3：询问 nums2 的元素总和
                ans.append(s)  # 把当前总和记录下来
        return ans  # 返回全部询问的答案
