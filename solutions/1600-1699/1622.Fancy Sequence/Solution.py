# 题目：1622. 奇妙序列（Fancy Sequence）
# 思路：用带「先乘后加」双懒标记的线段树维护序列，append 是单点赋值，addAll/multAll 是整段乘加，getIndex 是单点查询。
# 时间复杂度：append/addAll/multAll/getIndex 均为 O(log V)，V 为下标上限 1e5；空间复杂度：O(V)，动态开点的线段树。
MOD = 10**9 + 7  # 全局取模常量，所有运算结果都对它取模


class Node:  # 线段树节点：维护一段区间的和，以及「先乘后加」两个懒标记
    __slots__ = "left", "right", "l", "r", "mid", "v", "add", "mul"  # 用 __slots__ 限定属性名，减少内存占用并加快属性访问

    def __init__(self, l, r):  # 构造函数：只确定区间范围，标记保持默认值
        self.left = self.right = None  # 左右儿子初始为空，真正用到时才创建
        self.l, self.r = l, r  # 记录区间左右端点
        self.mid = (l + r) >> 1  # 右移一位等价于除以 2 求中点
        self.v = self.add = 0  # 区间和与加法标记初始为 0
        self.mul = 1  # 乘法标记初始为 1，表示不乘任何数


class SegmentTree:  # 线段树：支持区间乘、区间加与单点查询
    def __init__(self):  # 构造函数：建立覆盖 1..1e5+1 的根节点
        self.root = Node(1, 10**5 + 1)  # 区间上界取题目元素个数上限 1e5，再多留一位

    def modify(self, l, r, mul, add, node=None):  # 区间修改：对 [l, r] 先乘 mul 再加 add；node 默认从根开始
        if l > r:  # 待修改区间为空，无需处理
            return  # 直接返回
        if node is None:  # 未指定节点时从根节点开始
            node = self.root  # 把 node 指向根节点
        if node.l >= l and node.r <= r:  # 当前节点区间被待修改区间完全覆盖
            self.apply(node, mul, add)  # 整段打上懒标记，不再往下递归
            return  # 返回
        self.pushdown(node)  # 部分覆盖：先下推父节点已有的标记
        if l <= node.mid:  # 左子树与待修改区间有交集
            self.modify(l, r, mul, add, node.left)  # 递归修改左子树
        if r > node.mid:  # 右子树与待修改区间有交集
            self.modify(l, r, mul, add, node.right)  # 递归修改右子树
        self.pushup(node)  # 用儿子信息重算当前节点的区间和

    def query(self, l, r, node=None):  # 查询区间 [l, r] 的元素之和
        if l > r:  # 查询区间为空，贡献为 0
            return 0  # 返回 0
        if node is None:  # 未指定节点时从根节点开始
            node = self.root  # 把 node 指向根节点
        if node.l >= l and node.r <= r:  # 当前节点区间被查询区间完全覆盖
            return node.v  # 直接返回该节点维护好的区间和
        self.pushdown(node)  # 查询前先下推标记，保证儿子的 v 是最新值
        v = 0  # 累加查询结果的变量
        if l <= node.mid:  # 左子树与查询区间有交集
            v = (v + self.query(l, r, node.left)) % MOD  # 累加左子树结果并取模
        if r > node.mid:  # 右子树与查询区间有交集
            v = (v + self.query(l, r, node.right)) % MOD  # 累加右子树结果并取模
        return v  # 返回累加结果

    def apply(self, node, mul, add):  # 把「先乘 mul 再加 add」整体作用到 node 区间
        node.v = (node.v * mul + (node.r - node.l + 1) * add) % MOD  # 区间和更新：原和先乘 mul，再给每个元素加 add（共 len 个）
        node.add = (node.add * mul + add) % MOD  # 新的加法标记要叠在旧标记上：旧标记本身也要被乘一次
        node.mul = node.mul * mul % MOD  # 乘法标记直接累乘

    def pushup(self, node):  # 用儿子信息更新当前节点
        node.v = (node.left.v + node.right.v) % MOD  # 区间和等于左右儿子之和

    def pushdown(self, node):  # 把当前节点的懒标记下推给两个儿子
        if node.left is None:  # 左儿子不存在则创建
            node.left = Node(node.l, node.mid)  # 左儿子区间为 [l, mid]
        if node.right is None:  # 右儿子不存在则创建
            node.right = Node(node.mid + 1, node.r)  # 右儿子区间为 [mid+1, r]
        if node.add or node.mul != 1:  # 只有存在待下推的标记（加非 0 或乘非 1）时才继续
            self.apply(node.left, node.mul, node.add)  # 把标记作用到左儿子
            self.apply(node.right, node.mul, node.add)  # 把标记作用到右儿子
            node.add = 0  # 加法标记清零，表示已经下推
            node.mul = 1  # 乘法标记复位为 1，表示已经下推


class Fancy:  # 题目要求的 Fancy 类
    def __init__(self):  # 构造函数：初始化序列长度与线段树
        self.n = 0  # 序列初始为空
        self.tree = SegmentTree()  # 建立线段树

    def append(self, val: int) -> None:  # 在序列尾部追加一个值
        self.n += 1  # 元素个数加一，新元素下标就是 n
        self.tree.modify(self.n, self.n, 1, val)  # 单点「赋值」：乘 1 再加 val，等价于把第 n 个位置置为 val

    def addAll(self, inc: int) -> None:  # 给当前所有元素都加上 inc
        self.tree.modify(1, self.n, 1, inc)  # 对整个 [1, n] 区间做加法（乘法因子取 1）

    def multAll(self, m: int) -> None:  # 给当前所有元素都乘上 m
        self.tree.modify(1, self.n, m, 0)  # 对整个 [1, n] 区间做乘法（加法因子取 0）

    def getIndex(self, idx: int) -> int:  # 查询下标 idx（0 基）处的元素值
        return -1 if idx >= self.n else self.tree.query(idx + 1, idx + 1)  # 越界返回 -1，否则把 0 基下标转成 1 基做单点查询
