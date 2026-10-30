# 题目：2286. 以组为单位订音乐会的门票（Booking Concert Tickets in Groups）
# 核心思路：每行座位是线段树的叶子，结点维护「区间剩余座位和 s」与「区间单行剩余座位最大值 mx」；gather 用 mx 二分找最左可放行，scatter 先用 s 判断总量够不够，再从第一行有空的行走起贪心填满。
# 时间复杂度：每次 gather/scatter 为 O(log n + 被填满的行数)，总 O((n + q) log n)；空间复杂度：O(n)，线段树开 4n 个结点。
class Node:  # 线段树结点：保存一段行区间的统计信息
    __slots__ = "l", "r", "s", "mx"  # 用 __slots__ 限定属性，节省每个结点的内存

    def __init__(self):  # 初始化结点
        self.l = self.r = 0  # 区间左右端点先置 0，建树时再赋真值
        self.s = self.mx = 0  # 区间座位和与单行最大剩余座位都先置 0


class SegmentTree:  # 线段树：单点修改、区间求和、查最左满足条件的行
    def __init__(self, n, m):  # 构造函数：n 行，每行 m 个座位
        self.m = m  # 保存每行座位数，建树时叶子要用
        self.tr = [Node() for _ in range(n << 2)]  # 开 4n 个结点，n << 2 即 4n
        self.build(1, 1, n)  # 以 1 为根建树，负责区间 [1, n]

    def build(self, u, l, r):  # 递归建树：结点 u 负责区间 [l, r]
        self.tr[u].l, self.tr[u].r = l, r  # 记录当前结点负责的左右端点
        if l == r:  # 到达叶子，对应单独一行
            self.tr[u].s = self.tr[u].mx = self.m  # 这一行初始有 m 个空位，和与最大值都是 m
            return  # 叶子无需继续分裂，直接返回
        mid = (l + r) >> 1  # 取中点把区间分成两半
        self.build(u << 1, l, mid)  # 递归建左子树 [l, mid]
        self.build(u << 1 | 1, mid + 1, r)  # 递归建右子树 [mid+1, r]
        self.pushup(u)  # 用子结点信息更新当前结点

    def modify(self, u, x, v):  # 单点修改：把第 x 行的剩余座位改成 v
        if self.tr[u].l == x and self.tr[u].r == x:  # 已到叶子，且正是目标行
            self.tr[u].s = self.tr[u].mx = v  # 叶子只代表一行，和与最大值都设为 v
            return  # 修改完成直接返回
        mid = (self.tr[u].l + self.tr[u].r) >> 1  # 取区间中点
        if x <= mid:  # 目标行在左子树
            self.modify(u << 1, x, v)  # 递归修改左子结点
        else:  # 否则目标行在右子树
            self.modify(u << 1 | 1, x, v)  # 递归修改右子结点
        self.pushup(u)  # 回溯时重算当前结点的和与最大值

    def query_sum(self, u, l, r):  # 查询行区间 [l, r] 的剩余座位总数
        if self.tr[u].l >= l and self.tr[u].r <= r:  # 当前区间被查询区间完全覆盖
            return self.tr[u].s  # 直接返回该结点的座位和
        mid = (self.tr[u].l + self.tr[u].r) >> 1  # 取区间中点
        v = 0  # 答案累加器
        if l <= mid:  # 左子树与查询区间有交集
            v += self.query_sum(u << 1, l, r)  # 累加左子树的答案
        if r > mid:  # 右子树与查询区间有交集
            v += self.query_sum(u << 1 | 1, l, r)  # 累加右子树的答案
        return v  # 返回区间座位总数

    def query_idx(self, u, l, r, k):  # 在 [l, r] 中找最靠前且剩余座位 >= k 的行，找不到返回 0
        if self.tr[u].mx < k:  # 区间内单行最大值都不到 k，剪枝
            return 0  # 0 表示不存在这样的行
        if self.tr[u].l == self.tr[u].r:  # 到达叶子，说明这一行满足条件
            return self.tr[u].l  # 返回该行行号
        mid = (self.tr[u].l + self.tr[u].r) >> 1  # 取区间中点
        if self.tr[u << 1].mx >= k:  # 优先往左看，保证拿到最靠前的行
            return self.query_idx(u << 1, l, r, k)  # 递归左子树继续找
        if r > mid:  # 左边没有，且查询区间延伸到右半边
            return self.query_idx(u << 1 | 1, l, r, k)  # 递归右子树查找
        return 0  # 两边都没有，返回 0

    def pushup(self, u):  # 由子结点合并出父结点信息
        self.tr[u].s = self.tr[u << 1].s + self.tr[u << 1 | 1].s  # 座位和等于左右子树座位和相加
        self.tr[u].mx = max(self.tr[u << 1].mx, self.tr[u << 1 | 1].mx)  # 最大值取左右子树最大值的较大者


class BookMyShow:  # 题目要求的订票类
    def __init__(self, n: int, m: int):  # 构造函数：n 行，每行 m 个座位
        self.n = n  # 保存行数，scatter 要遍历到第 n 行
        self.tree = SegmentTree(n, m)  # 建线段树，初始每行 m 个空位

    def gather(self, k: int, maxRow: int) -> List[int]:  # gather：在 0..maxRow 行内找一整段连续 k 个座位
        maxRow += 1  # 行号从 0 基转成 1 基
        i = self.tree.query_idx(1, 1, maxRow, k)  # 找最靠前且剩余座位 >= k 的行
        if i == 0:  # 没有满足条件的行
            return []  # 按题目要求返回空列表
        s = self.tree.query_sum(1, i, i)  # 第 i 行当前剩余座位数
        self.tree.modify(1, i, s - k)  # 这一行扣掉 k 个座位并写回线段树
        return [i - 1, self.tree.m - s]  # 返回 0 基行号和这一行被占用的起始列号

    def scatter(self, k: int, maxRow: int) -> bool:  # scatter：把 k 个座位分散订在 0..maxRow 行内
        maxRow += 1  # 行号转成 1 基
        if self.tree.query_sum(1, 1, maxRow) < k:  # 前 maxRow 行总空位不足 k 个
            return False  # 直接返回失败
        i = self.tree.query_idx(1, 1, maxRow, 1)  # 找第一行还有空位的行，前面都已坐满
        for j in range(i, self.n + 1):  # 从这一行开始往后依次占用空位
            s = self.tree.query_sum(1, j, j)  # 第 j 行剩余座位数
            if s >= k:  # 这一行够放下剩余的 k 个
                self.tree.modify(1, j, s - k)  # 扣掉 k 个座位写回
                return True  # 安排完毕，返回成功
            k -= s  # 这一行坐满，还需再找 k - s 个
            self.tree.modify(1, j, 0)  # 把这一行剩余座位清成 0
        return True  # 总数已保证够，循环走完即成功


# Your BookMyShow object will be instantiated and called as such:
# obj = BookMyShow(n, m)
# param_1 = obj.gather(k,maxRow)
# param_2 = obj.scatter(k,maxRow)
