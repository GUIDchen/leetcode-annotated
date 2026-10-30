# 3454. 分割正方形 II / Separate Squares II
# 核心思路：扫描线求正方形并集面积，用线段树维护当前 x 方向被覆盖的总长度，再在第二遍扫描中定位面积刚好达到一半的高度。
# 复杂度：时间复杂度 O(n log n)，空间复杂度 O(n)。
class Node:  # 线段树结点
    __slots__ = ("l", "r", "cnt", "length")  # 限定属性名以节省内存

    def __init__(self):  # 初始化结点
        self.l = self.r = 0  # 区间左右端点下标
        self.cnt = self.length = 0  # 整段被覆盖的次数与覆盖总长度


class SegmentTree:  # 维护“被覆盖总长度”的线段树
    def __init__(self, nums):  # 用离散坐标建树
        n = len(nums) - 1  # 相邻坐标构成的小区间个数
        self.nums = nums  # 保存坐标数组
        self.tr = [Node() for _ in range(n << 2)]  # 按 4n 预分配结点
        self.build(1, 0, n - 1)  # 从根结点开始建树

    def build(self, u, l, r):  # 建树：结点 u 管理区间 [l, r]
        self.tr[u].l, self.tr[u].r = l, r  # 记录区间左右端点下标
        if l != r:  # 非叶结点继续递归建子树
            mid = (l + r) >> 1  # 区间中点
            self.build(u << 1, l, mid)  # 建左子树
            self.build(u << 1 | 1, mid + 1, r)  # 建右子树

    def modify(self, u, l, r, k):  # 把区间 [l, r] 的覆盖次数增加 k
        if self.tr[u].l >= l and self.tr[u].r <= r:  # 当前区间被修改区间完全包含
            self.tr[u].cnt += k  # 直接累加覆盖标记
        else:  # 只有部分相交，需要往子结点递归
            mid = (self.tr[u].l + self.tr[u].r) >> 1  # 区间中点
            if l <= mid:  # 左子树有交集
                self.modify(u << 1, l, r, k)  # 递归左子树
            if r > mid:  # 右子树有交集
                self.modify(u << 1 | 1, l, r, k)  # 递归右子树
        self.pushup(u)  # 回溯时更新当前结点的覆盖长度

    def pushup(self, u):  # 由子结点信息更新结点 u 的覆盖长度
        if self.tr[u].cnt:  # 该区间被整体覆盖
            self.tr[u].length = self.nums[self.tr[u].r + 1] - self.nums[self.tr[u].l]  # 覆盖长度即为整段坐标跨度
        elif self.tr[u].l == self.tr[u].r:  # 叶子结点且未被整体覆盖
            self.tr[u].length = 0  # 没有覆盖，长度为 0
        else:  # 内部结点且未被整体覆盖
            self.tr[u].length = self.tr[u << 1].length + self.tr[u << 1 | 1].length  # 由左右子结点长度合并

    @property
    def length(self):  # 查询整条扫描线被覆盖的总长度
        return self.tr[1].length  # 根结点的长度即为答案


class Solution:  # 题解类
    def separateSquares(self, squares: List[List[int]]) -> float:  # 求使上下两部分面积相等的最小高度
        xs = set()  # 收集所有 x 坐标，用于离散化
        segs = []  # 扫描线事件：(y, x1, x2, 增量)
        for x1, y1, l in squares:  # 把每个正方形拆成底边与顶边两条事件
            x2, y2 = x1 + l, y1 + l  # 右上角坐标
            xs.update([x1, x2])  # 记录左右边界
            segs.append((y1, x1, x2, 1))  # 底边事件：进入时覆盖次数 +1
            segs.append((y2, x1, x2, -1))  # 顶边事件：离开时覆盖次数 -1
        segs.sort()  # 事件按高度升序排序
        st = sorted(xs)  # 离散化后的 x 坐标数组
        tree = SegmentTree(st)  # 用离散坐标建线段树
        d = {x: i for i, x in enumerate(st)}  # x 坐标到离散下标的映射
        area = 0  # 第一遍扫描累计并集总面积
        y0 = 0  # 上一条扫描线的高度
        for y, x1, x2, k in segs:  # 第一遍扫描：求正方形并集的总面积
            area += (y - y0) * tree.length  # 累加两条扫描线之间矩形条的面积
            tree.modify(1, d[x1], d[x2] - 1, k)  # 更新当前扫描线的覆盖情况
            y0 = y  # 记录本次扫描线高度

        target = area / 2  # 上下各一半，因此目标面积为总面积的一半
        area = 0  # 复用 area 记录第二遍扫描的下方面积
        y0 = 0  # 重置扫描线高度
        for y, x1, x2, k in segs:  # 第二遍扫描：定位面积刚好达到一半的高度
            t = (y - y0) * tree.length  # 当前矩形条的面积
            if area + t >= target:  # 目标面积落在这一条内
                return y0 + (target - area) / tree.length  # 按比例线性插值出精确高度
            area += t  # 累加已经扫过的面积
            tree.modify(1, d[x1], d[x2] - 1, k)  # 更新覆盖情况
            y0 = y  # 记录本次扫描线高度
        return 0  # 理论上不会走到这里，保底返回
