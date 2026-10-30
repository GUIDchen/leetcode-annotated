# 题目：715. Range 模块（Range Module）
# 核心思路：动态开点线段树。值域是 [1, 1e9]，每个节点维护「整段是否被完全跟踪」(v) 与懒标记 (add)，addRange/removeRange 做区间赋值，queryRange 做区间与查询，子节点按需创建。
# 时间复杂度：每次 addRange/removeRange/queryRange 均为 O(log C)，C = 1e9；空间复杂度：O(k·log C)，k 为操作次数，节点按需创建。
class Node:  # 线段树节点：用 __slots__ 省内存并加快属性访问
    __slots__ = ['left', 'right', 'add', 'v']  # 限定实例属性集合，避免为每个节点创建 __dict__

    def __init__(self):  # 初始化节点：初始没有子节点、没有懒标记、未被跟踪
        self.left = None  # 左子节点，动态开点（真正用到时才创建）
        self.right = None  # 右子节点
        self.add = 0  # 懒标记：1 表示整段被跟踪，-1 表示整段被清除，0 表示无标记
        self.v = False  # 该区间是否被完全跟踪（线段树维护的答案）


class SegmentTree:  # 动态开点的线段树，值域固定为 [1, 1e9]
    __slots__ = ['root']  # 只允许一个实例属性 root

    def __init__(self):  # 构造函数：创建根节点
        self.root = Node()  # 根节点对应整个值域

    def modify(self, left, right, v, l=1, r=int(1e9), node=None):  # 区间赋值：把 [left, right] 设成 v，默认从整段值域开始递归
        if node is None:  # 首次调用没有传入节点，说明要从根开始
            node = self.root  # 用根节点作为当前节点
        if l >= left and r <= right:  # 当前区间被目标区间完全包含，可以整段打标记
            if v == 1:  # v 为 1 表示要把这段设为被跟踪
                node.add = 1  # 设置懒标记为「覆盖」
                node.v = True  # 该区间置为完全跟踪
            else:  # 否则表示要把这段清除
                node.add = -1  # 设置懒标记为「清除」
                node.v = False  # 该区间置为未跟踪
            return  # 整段已处理完，直接返回，不再往下递归
        self.pushdown(node)  # 要继续进入子区间，先把懒标记下推并确保子节点存在
        mid = (l + r) >> 1  # 取区间中点，把 [l, r] 划分成左右两半
        if left <= mid:  # 目标区间与左子区间有交集
            self.modify(left, right, v, l, mid, node.left)  # 递归修改左子树
        if right > mid:  # 目标区间与右子区间有交集
            self.modify(left, right, v, mid + 1, r, node.right)  # 递归修改右子树
        self.pushup(node)  # 子节点更新完后，重新汇总当前节点的覆盖状态

    def query(self, left, right, l=1, r=int(1e9), node=None):  # 区间查询：判断 [left, right] 是否被完全跟踪
        if node is None:  # 首次调用没有传入节点，说明要从根开始
            node = self.root  # 用根节点作为当前节点
        if l >= left and r <= right:  # 当前区间被完全包含，可以直接给出答案
            return node.v  # 返回该区间维护的覆盖标记
        self.pushdown(node)  # 需要查看子区间，先把懒标记下推
        mid = (l + r) >> 1  # 取区间中点划分左右两半
        v = True  # 以「全部覆盖」作为初值，便于用逻辑与累积结果
        if left <= mid:  # 目标区间与左子区间有交集
            v = v and self.query(left, right, l, mid, node.left)  # 与左子树的查询结果求逻辑与
        if right > mid:  # 目标区间与右子区间有交集
            v = v and self.query(left, right, mid + 1, r, node.right)  # 与右子树的查询结果求逻辑与
        return v  # 只要有一个子区间未被覆盖，整体就不算完全覆盖

    def pushup(self, node):  # 由左右子节点的覆盖情况反推父节点的覆盖状态
        node.v = bool(node.left and node.left.v and node.right and node.right.v)  # 两个子节点都存在且都被完全跟踪时，父节点才算完全跟踪（bool 转成真正的布尔值）

    def pushdown(self, node):  # 把父节点的懒标记下推给子节点（动态开点：需要时才创建）
        if node.left is None:  # 左子节点还不存在
            node.left = Node()  # 先创建左子节点
        if node.right is None:  # 右子节点还不存在
            node.right = Node()  # 先创建右子节点
        if node.add:  # 只有当懒标记非 0 时才需要下推
            node.left.add = node.right.add = node.add  # 把标记原样复制给左右两个子节点
            node.left.v = node.add == 1  # 左子节点的覆盖状态与标记保持一致
            node.right.v = node.add == 1  # 右子节点的覆盖状态与标记保持一致
            node.add = 0  # 清空当前节点的标记，避免以后重复下推


class RangeModule:  # 题目要求的 RangeModule 类，内部用线段树维护被跟踪的整数区间
    def __init__(self):  # 构造函数：创建底层线段树
        self.tree = SegmentTree()  # 线段树覆盖 [1, 1e9] 的整数点

    def addRange(self, left: int, right: int) -> None:  # 把左闭右开区间 [left, right) 标记为被跟踪
        self.tree.modify(left, right - 1, 1)  # 题目右端点是开区间，转成闭区间 [left, right-1] 后整段置为覆盖

    def queryRange(self, left: int, right: int) -> bool:  # 查询左闭右开区间 [left, right) 是否被完整跟踪
        return self.tree.query(left, right - 1)  # 同样转成闭区间 [left, right-1] 后整段查询

    def removeRange(self, left: int, right: int) -> None:  # 把左闭右开区间 [left, right) 取消跟踪
        self.tree.modify(left, right - 1, -1)  # 转成闭区间 [left, right-1] 后整段置为未覆盖


# Your RangeModule object will be instantiated and called as such:
# obj = RangeModule()
# obj.addRange(left,right)
# param_2 = obj.queryRange(left,right)
# obj.removeRange(left,right)
