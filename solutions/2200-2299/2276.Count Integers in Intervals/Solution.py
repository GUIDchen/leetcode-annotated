# 题目：2276. 统计区间中的整数数目（Count Integers in Intervals）
# 思路：动态开点线段树维护 [1, 1e9] 的覆盖情况，add 做区间置 1，count 做全域求和，懒标记控制下传。
# 时间复杂度：add 与 count 均为 O(log C)，C = 1e9；空间复杂度：O(k log C)，k 为加入的区间个数。
class Node:  # 线段树节点：表示闭区间 [l, r]
    __slots__ = ("left", "right", "l", "r", "mid", "v", "add")  # 用 __slots__ 固定属性名，减少每个节点的内存占用

    def __init__(self, l, r):  # 构造节点，区间端点由外部传入
        self.left = None  # 左子节点，初始为空，按需创建
        self.right = None  # 右子节点，初始为空，按需创建
        self.l = l  # 区间左端点
        self.r = r  # 区间右端点
        self.mid = (l + r) // 2  # 区间中点，向下取整，用来划分左右子区间
        self.v = 0  # 该区间内已被覆盖的整数个数
        self.add = 0  # 懒标记：0 表示无标记，1 表示整段被覆盖


class SegmentTree:  # 动态开点线段树：支持区间置 1 与区间求和
    def __init__(self):  # 初始化：建立根节点
        self.root = Node(1, int(1e9) + 1)  # 根覆盖 [1, 1e9+1]，右端点多留 1，便于 count 查询 [1, 1e9]

    def modify(self, l, r, v, node=None):  # 把区间 [l, r] 全部置为 v（本题只用 v = 1）
        if node is None:  # 默认参数：未显式传入节点时从根开始
            node = self.root  # 使用根节点作为递归起点
        if l > r:  # 空区间无需处理
            return  # 直接返回
        if node.l >= l and node.r <= r:  # 当前节点区间被 [l, r] 完全覆盖
            node.v = node.r - node.l + 1  # 整段整数都算被覆盖，计数等于区间长度
            node.add = v  # 打上懒标记，暂不下传，保证复杂度
            return  # 完全覆盖后无需继续递归
        self.pushdown(node)  # 部分覆盖：先下传懒标记
        if l <= node.mid:  # 与左子区间有交集
            self.modify(l, r, v, node.left)  # 递归处理左子树
        if r > node.mid:  # 与右子区间有交集
            self.modify(l, r, v, node.right)  # 递归处理右子树
        self.pushup(node)  # 用子节点结果回填当前节点

    def query(self, l, r, node=None):  # 查询区间 [l, r] 内被覆盖的整数个数
        if node is None:  # 默认参数：未显式传入节点时从根开始
            node = self.root  # 使用根节点作为查询起点
        if l > r:  # 空区间对答案贡献为 0
            return 0  # 返回 0
        if node.l >= l and node.r <= r:  # 查询区间完全覆盖当前节点
            return node.v  # 直接返回该节点的覆盖计数
        self.pushdown(node)  # 下传懒标记，之后子节点的值才正确
        v = 0  # 累计左右子树的查询结果
        if l <= node.mid:  # 左子区间与查询区间有交集
            v += self.query(l, r, node.left)  # 加上左子树的贡献
        if r > node.mid:  # 右子区间与查询区间有交集
            v += self.query(l, r, node.right)  # 加上右子树的贡献
        return v  # 返回闭区间 [l, r] 的覆盖总数

    def pushup(self, node):  # 由两个子节点汇总当前节点
        node.v = node.left.v + node.right.v  # 覆盖计数等于左右子树之和

    def pushdown(self, node):  # 下传懒标记，并按需动态创建子节点
        if node.left is None:  # 左子节点尚未创建
            node.left = Node(node.l, node.mid)  # 动态开点：建立左子区间 [l, mid]
        if node.right is None:  # 右子节点尚未创建
            node.right = Node(node.mid + 1, node.r)  # 动态开点：建立右子区间 [mid+1, r]
        if node.add != 0:  # 有懒标记时才需要下传
            left, right = node.left, node.right  # 同时取出左右子节点，便于后续赋值
            left.add = node.add  # 左子节点继承覆盖标记
            right.add = node.add  # 右子节点继承覆盖标记
            left.v = left.r - left.l + 1  # 左子区间整段被覆盖
            right.v = right.r - right.l + 1  # 右子区间整段被覆盖
            node.add = 0  # 清除当前节点的标记，防止重复下传


class CountIntervals:  # 题目要求的计数类
    def __init__(self):  # 构造函数
        self.tree = SegmentTree()  # 内部维护一棵动态开点线段树

    def add(self, left, right):  # 把区间 [left, right] 加入集合
        self.tree.modify(left, right, 1)  # 线段树区间置 1，表示这些整数已被覆盖

    def count(self):  # 返回当前集合中不同整数的个数
        return self.tree.query(1, int(1e9))  # 查询全域 [1, 1e9] 的覆盖计数，即答案


# Your CountIntervals object will be instantiated and called as such:
# obj = CountIntervals()
# obj.add(left, right)
# param_2 = obj.count()
