# 题目：850. 矩形面积 II（Rectangle Area II）
# 思路：扫描线 + y 坐标离散化 + 线段树维护当前被覆盖的 y 总长度，沿 x 方向累加「宽度 × 覆盖长度」得到并集面积。
# 时间复杂度：O(n log n)，排序与 n 次线段树区间更新；空间复杂度：O(n)，离散化坐标表与线段树节点。
class Node:  # 线段树节点：区间端点、覆盖次数、有效覆盖长度
    def __init__(self):  # 初始化节点
        self.l = self.r = 0  # 区间左右端点初始为 0
        self.cnt = self.length = 0  # 覆盖次数与有效长度初始为 0


class SegmentTree:  # y 方向线段树：支持区间加与整体覆盖长度查询
    def __init__(self, nums):  # nums 是离散化后的 y 坐标表
        n = len(nums) - 1  # s 个坐标点划分出 s-1 个小区间，故区间下标为 0..n-1
        self.nums = nums  # 保存坐标表，pushup 时用来还原真实长度
        self.tr = [Node() for _ in range(n << 2)]  # 节点数组开 4n 个（n << 2 即 4n）
        self.build(1, 0, n - 1)  # 从根节点 1 开始，构建覆盖 [0, n-1] 的线段树

    def build(self, u, l, r):  # u 为节点编号，[l, r] 为该节点负责的下标区间
        self.tr[u].l, self.tr[u].r = l, r  # 同时记录区间左右端点
        if l != r:  # 非叶子节点继续分裂
            mid = (l + r) >> 1  # 中点，>> 1 等价于整除 2
            self.build(u << 1, l, mid)  # 递归建左子树 u*2
            self.build(u << 1 | 1, mid + 1, r)  # 递归建右子树 u*2+1

    def modify(self, u, l, r, k):  # 区间加：把 [l, r] 的覆盖次数加上 k
        if self.tr[u].l >= l and self.tr[u].r <= r:  # 当前节点区间被完全包含，直接打标记
            self.tr[u].cnt += k  # 覆盖次数累加 k，不再向下递归
        else:  # 否则需要继续向下递归
            mid = (self.tr[u].l + self.tr[u].r) >> 1  # 当前节点区间的中点
            if l <= mid:  # 左半区间与操作区间相交则递归左子树
                self.modify(u << 1, l, r, k)  # 递归更新左子树
            if r > mid:  # 右半区间与操作区间相交则递归右子树
                self.modify(u << 1 | 1, l, r, k)  # 递归更新右子树
        self.pushup(u)  # 回溯时重新计算本节点覆盖长度

    def pushup(self, u):  # 由子节点信息更新节点 u 的 length
        if self.tr[u].cnt:  # 被完整覆盖时整段 y 都有效
            self.tr[u].length = self.nums[self.tr[u].r + 1] - self.nums[self.tr[u].l]  # 用离散化坐标还原真实长度：nums[r+1] - nums[l]
        elif self.tr[u].l == self.tr[u].r:  # 叶子且未被覆盖，长度为 0
            self.tr[u].length = 0  # 长度置 0
        else:  # 非叶子且未被整体覆盖，由子节点长度拼接
            self.tr[u].length = self.tr[u << 1].length + self.tr[u << 1 | 1].length  # 左右子节点长度之和即本节点长度

    @property  # 用属性方式暴露根节点的覆盖总长度
    def length(self):  # 查询整体覆盖总长度
        return self.tr[1].length  # 根节点的 length 即 y 方向并集长度


class Solution:  # 题解类
    def rectangleArea(self, rectangles: List[List[int]]) -> int:  # rectangles 每个元素是 [x1, y1, x2, y2]，返回并集面积
        segs = []  # 存放扫描线事件 (x, y1, y2, k)
        alls = set()  # 收集所有 y 坐标用于离散化
        for x1, y1, x2, y2 in rectangles:  # 遍历矩形，拆出左右两条竖边
            segs.append((x1, y1, y2, 1))  # 左边事件：覆盖数 +1
            segs.append((x2, y1, y2, -1))  # 右边事件：覆盖数 -1
            alls.update([y1, y2])  # 记录上下边界坐标

        segs.sort()  # 按 x 升序排序，保证按扫描方向处理
        alls = sorted(alls)  # 去重并升序得到离散化坐标表
        tree = SegmentTree(alls)  # 建立 y 方向线段树
        m = {v: i for i, v in enumerate(alls)}  # y 坐标 → 离散化下标的映射
        ans = 0  # 累加面积
        for i, (x, y1, y2, k) in enumerate(segs):  # 依次处理每条扫描线事件
            if i:  # 从第二条扫描线开始才能结算带宽面积
                ans += tree.length * (x - segs[i - 1][0])  # 宽度 × 当前 y 覆盖长度
            tree.modify(1, m[y1], m[y2] - 1, k)  # 更新该事件的 y 区间；m[y2]-1 因为区间按左闭右开映射
        ans %= int(1e9 + 7)  # 对 1e9+7 取模
        return ans  # 返回并集面积
