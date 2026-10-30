# 题目：732. 我的日程安排表 III（My Calendar III）
# 思路：用动态开点线段树维护时间轴上的「区间加 1 + 查询全局最大值」，每次 book 把 [start, end) 加 1，再查询整段区间的最大重叠次数。
# 时间复杂度：每次 book 为 O(log C)，C 为时间轴范围 1e9；空间复杂度：O(k log C)，k 为预订次数（节点按需创建）。
class Node:  # 线段树节点：维护自己覆盖区间内的最大重叠次数与懒标记
    def __init__(self, l, r):  # 构造函数：以区间 [l, r] 建立节点
        self.left = None  # 左儿子，动态开点，用到时才创建
        self.right = None  # 右儿子，动态开点，用到时才创建
        self.l = l  # 当前节点覆盖区间的左端点
        self.r = r  # 当前节点覆盖区间的右端点
        self.mid = (l + r) >> 1  # 右移一位等价于除以 2，得到区间中点
        self.v = 0  # 本区间内的最大重叠次数
        self.add = 0  # 懒标记：整段区间尚未下发给儿子的增量


class SegmentTree:  # 动态开点线段树：支持区间加与查询区间最大值
    def __init__(self):  # 构造函数：根节点覆盖整条时间轴 [1, 1e9+1]
        self.root = Node(1, int(1e9 + 1))  # 把 1e9+1 转成 int；整体右移一位以适配 1-based 时间轴

    def modify(self, l: int, r: int, v: int, node: Node = None):  # 对区间 [l, r] 上的所有时刻整体加上 v；node 为 None 时表示从根开始
        if l > r:  # 空区间直接返回（防御性判断）
            return  # 无需处理
        if node is None:  # 没有传入节点说明是对外调用，从根节点开始
            node = self.root  # 把 node 指向根节点
        if node.l >= l and node.r <= r:  # 当前节点区间被 [l, r] 完全覆盖，可以打懒标记
            node.v += v  # 本区间最大值整体加 v
            node.add += v  # 懒标记累积，留给儿子以后再加
            return  # 完全覆盖后无需继续下探
        self.pushdown(node)  # 先保证儿子存在，并把父亲的懒标记下发
        if l <= node.mid:  # 左半边与修改区间有交集
            self.modify(l, r, v, node.left)  # 递归修改左儿子
        if r > node.mid:  # 右半边与修改区间有交集
            self.modify(l, r, v, node.right)  # 递归修改右儿子
        self.pushup(node)  # 两个儿子都更新完，用它们的最大值回填父亲

    def query(self, l: int, r: int, node: Node = None) -> int:  # 查询区间 [l, r] 内的最大重叠次数；node 为 None 时从根开始
        if l > r:  # 空区间返回 0
            return 0  # 不产生任何贡献
        if node is None:  # 没有传入节点说明是对外调用，从根节点开始
            node = self.root  # 把 node 指向根节点
        if node.l >= l and node.r <= r:  # 被完全覆盖时直接返回节点自己维护的最大值
            return node.v  # 直接返回该区间的最大值
        self.pushdown(node)  # 保证儿子的值已经包含父亲的懒标记
        v = 0  # v 收集两个子区间查询结果的最大值
        if l <= node.mid:  # 左半边有交集
            v = max(v, self.query(l, r, node.left))  # 与左儿子的查询结果取最大
        if r > node.mid:  # 右半边有交集
            v = max(v, self.query(l, r, node.right))  # 与右儿子的查询结果取最大
        return v  # 返回本区间内查询到的最大值

    def pushup(self, node: Node):  # 用两个儿子的最大值更新父亲
        node.v = max(node.left.v, node.right.v)  # 父亲的最大值取两个儿子最大值的较大者

    def pushdown(self, node: Node):  # 把本节点的懒标记下发给两个儿子
        if node.left is None:  # 左儿子还不存在
            node.left = Node(node.l, node.mid)  # 动态开点，建立覆盖 [l, mid] 的左儿子
        if node.right is None:  # 右儿子还不存在
            node.right = Node(node.mid + 1, node.r)  # 动态开点，建立覆盖 [mid+1, r] 的右儿子
        if node.add:  # 只有存在懒标记才需要下发
            node.left.v += node.add  # 左儿子的最大值加上标记
            node.right.v += node.add  # 右儿子的最大值加上标记
            node.left.add += node.add  # 标记继续累积到左儿子，供更下层使用
            node.right.add += node.add  # 标记继续累积到右儿子
            node.add = 0  # 清空父亲的懒标记，避免重复下发


class MyCalendarThree:  # 题目要求的日程安排表 III：每次预订后返回最大重叠次数
    def __init__(self):  # 构造函数：创建线段树
        self.tree = SegmentTree()  # 根节点覆盖整条时间轴

    def book(self, start: int, end: int) -> int:  # 预订半开区间 [start, end)，返回当前全局最大重叠次数
        self.tree.modify(start + 1, end, 1)  # 把区间整体加 1；+1 是为了和线段树 1-based 的时间轴对齐
        return self.tree.query(1, int(1e9 + 1))  # 查询整条时间轴上的最大值，即当前最大重叠次数


# 下面是 LeetCode 判题器自动生成的调用示例，原样保留，仅作说明
# Your MyCalendarThree object will be instantiated and called as such:  # 判题器给出的调用示例，原样保留
# obj = MyCalendarThree()  # 示例：构造对象
# param_1 = obj.book(start,end)  # 示例：调用 book
