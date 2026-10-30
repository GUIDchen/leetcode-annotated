# 题目：2407. 最长递增子序列 II（Longest Increasing Subsequence II）
# 思路：值域线段树维护「以值 x 结尾的最长合法子序列长度」，处理 v 时查询区间 [v-k, v-1] 的最大值再加一，然后把结果单点写回 v。
# 时间复杂度：O(n log M)，n 为元素个数，M 为元素最大值；空间复杂度：O(M)，线段树需要约 4M 个节点。
class Node:  # 线段树节点，保存区间左右端点与区间最大值
    def __init__(self):  # 构造函数：把节点属性初始化为 0
        self.l = 0  # 区间左端点
        self.r = 0  # 区间右端点
        self.v = 0  # 该区间内的最大值，即区间内最长合法子序列长度


class SegmentTree:  # 值域线段树：下标代表元素值，节点维护该值域内的最大长度
    def __init__(self, n):  # n 表示值域上界
        self.tr = [Node() for _ in range(4 * n)]  # 节点数上界为 4n，一次性建好整棵树
        self.build(1, 1, n)  # 以 1 号节点为根，覆盖值域 [1, n] 建树

    def build(self, u, l, r):  # 以 u 为根，建立覆盖区间 [l, r] 的子树
        self.tr[u].l = l  # 记录该节点管辖范围的左端
        self.tr[u].r = r  # 记录该节点管辖范围的右端
        if l == r:  # 到达叶子节点，无需再分裂
            return  # 直接返回，结束这条递归分支
        mid = (l + r) >> 1  # 取中点把区间二分
        self.build(u << 1, l, mid)  # 递归构建左子树，覆盖 [l, mid]
        self.build(u << 1 | 1, mid + 1, r)  # 递归构建右子树，覆盖 [mid+1, r]

    def modify(self, u, x, v):  # 单点更新：把下标 x 处的值改成 v
        if self.tr[u].l == x and self.tr[u].r == x:  # 定位到只包含 x 的叶子节点
            self.tr[u].v = v  # 直接覆盖为新的长度
            return  # 更新完成，回溯返回
        mid = (self.tr[u].l + self.tr[u].r) >> 1  # 用当前区间中点决定往哪棵子树递归
        if x <= mid:  # x 落在左半区间
            self.modify(u << 1, x, v)  # 递归更新左子树
        else:  # 否则 x 落在右半区间
            self.modify(u << 1 | 1, x, v)  # 递归更新右子树
        self.pushup(u)  # 回溯时刷新当前节点的最大值

    def pushup(self, u):  # 用左右孩子的较大值刷新父亲节点
        self.tr[u].v = max(self.tr[u << 1].v, self.tr[u << 1 | 1].v)  # 区间最大值等于两个孩子的较大者

    def query(self, u, l, r):  # 查询区间 [l, r] 内的最大值
        if self.tr[u].l >= l and self.tr[u].r <= r:  # 当前节点被查询区间完全覆盖
            return self.tr[u].v  # 直接返回节点维护的值
        mid = (self.tr[u].l + self.tr[u].r) >> 1  # 否则按中点拆分查询区间
        v = 0  # 候选答案，长度非负，初值取 0
        if l <= mid:  # 左子区间与查询区间有交集
            v = self.query(u << 1, l, r)  # 先递归查询左子树
        if r > mid:  # 右子区间与查询区间有交集
            v = max(v, self.query(u << 1 | 1, l, r))  # 与右侧结果取较大值
        return v  # 返回该区间的最大值


class Solution:  # LeetCode 约定的题解类
    def lengthOfLIS(self, nums: List[int], k: int) -> int:  # nums：输入数组；k：子序列中相邻元素差的上限
        tree = SegmentTree(max(nums))  # 值域上界取数组最大值后建树
        ans = 1  # 数组非空，答案至少为 1
        for v in nums:  # 依次处理每个元素
            t = tree.query(1, v - k, v - 1) + 1  # 只允许从前驱区间 [v-k, v-1] 转移，长度加一
            ans = max(ans, t)  # 更新全局最优解
            tree.modify(1, v, t)  # 把以 v 结尾的最长长度写回线段树
        return ans  # 返回最长递增子序列的长度
