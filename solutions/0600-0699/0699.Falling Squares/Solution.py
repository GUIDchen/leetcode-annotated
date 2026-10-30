# 题目：699. 掉落的方块（Falling Squares）
# 思路：坐标范围可达 1e9，用动态开点的线段树维护每个坐标区间的最高高度；每块方块先查询覆盖区间的最大高度并叠加上自身边长，再区间赋值，答案取历史最大值。
# 时间复杂度：O(n log C)，每次查询与修改都是 log 级，C 为坐标上界 1e9；空间复杂度：O(n log C)，动态开点只为被访问的区间创建结点。
class Node:  # 线段树结点：表示坐标区间 [l, r] 上的高度信息
    def __init__(self, l, r):  # 构造函数：给定区间端点创建一个结点
        self.left = None  # 左儿子，用到时才动态创建
        self.right = None  # 右儿子，用到时才动态创建
        self.l = l  # 当前结点负责区间的左端点
        self.r = r  # 当前结点负责区间的右端点
        self.mid = (l + r) >> 1  # 用右移一位实现除以 2，得到区间中点
        self.v = 0  # 该区间内的最大高度，初始为 0
        self.add = 0  # 懒标记：非 0 表示整段区间被统一赋值为 add


class SegmentTree:  # 动态开点线段树，维护区间最大值并支持区间赋值
    def __init__(self):  # 构造函数：建立表示整个坐标范围的根结点
        self.root = Node(1, int(1e9))  # 根区间取 [1, 1e9]，因为方块横坐标与边长之和不超 1e9

    def modify(self, l, r, v, node=None):  # 把区间 [l, r] 的高度统一改成 v；node 为 None 时表示从根开始
        if l > r:  # 空区间没有意义
            return  # 直接返回，作为递归的兜底
        if node is None:  # 没有显式传入结点，说明这是对外调用
            node = self.root  # 默认从根结点开始递归
        if node.l >= l and node.r <= r:  # 当前结点区间被目标区间完全覆盖
            node.v = v  # 整段高度统一赋值，最大值自然就是 v
            node.add = v  # 打上懒标记，等子结点被访问时再下传
            return  # 覆盖完毕，无需继续向下递归
        self.pushdown(node)  # 未完全覆盖，先把懒标记下传
        if l <= node.mid:  # 目标区间与左半段有交集
            self.modify(l, r, v, node.left)  # 递归修改左子树
        if r > node.mid:  # 目标区间与右半段有交集
            self.modify(l, r, v, node.right)  # 递归修改右子树
        self.pushup(node)  # 子结点更新后，重新计算当前结点的最大值

    def query(self, l, r, node=None):  # 查询区间 [l, r] 内的最大高度；node 为 None 时表示从根开始
        if l > r:  # 空区间没有高度
            return 0  # 返回 0 作为中性值
        if node is None:  # 没有显式传入结点，说明这是对外调用
            node = self.root  # 默认从根结点开始递归
        if node.l >= l and node.r <= r:  # 当前结点区间被完全覆盖
            return node.v  # 直接返回该区间记录的最大值
        self.pushdown(node)  # 进入子结点前先下传懒标记，保证子结点数据正确
        v = 0  # 记录本次查询的答案，初始为 0（高度非负）
        if l <= node.mid:  # 与左半段有交集
            v = max(v, self.query(l, r, node.left))  # 用左子树的查询结果更新答案
        if r > node.mid:  # 与右半段有交集
            v = max(v, self.query(l, r, node.right))  # 用右子树的查询结果更新答案
        return v  # 返回两个子区间中的较大高度

    def pushup(self, node):  # 用子结点的值更新父结点的最大值
        node.v = max(node.left.v, node.right.v)  # 父区间最大值等于左右儿子最大值的较大者

    def pushdown(self, node):  # 访问子结点之前，把当前结点的懒标记下传
        if node.left is None:  # 左儿子还没创建
            node.left = Node(node.l, node.mid)  # 按左半区间动态创建左儿子
        if node.right is None:  # 右儿子还没创建
            node.right = Node(node.mid + 1, node.r)  # 按右半区间动态创建右儿子
        if node.add:  # 当前结点带有「整段赋值」的懒标记
            node.left.v = node.add  # 把赋值结果传给左儿子的最大值
            node.right.v = node.add  # 把赋值结果传给右儿子的最大值
            node.left.add = node.add  # 左儿子也打上同样的懒标记，供更下层使用
            node.right.add = node.add  # 右儿子也打上同样的懒标记，供更下层使用
            node.add = 0  # 标记已下传，清空当前结点的懒标记


class Solution:  # LeetCode 约定的题解类
    def fallingSquares(self, positions: List[List[int]]) -> List[int]:  # positions[i] = [left, size] 表示第 i 块方块的左边界与边长
        ans = []  # 依次记录每块方块落下后的全局最高高度
        mx = 0  # 当前的全局最大高度
        tree = SegmentTree()  # 建立线段树来维护坐标轴上的高度
        for l, w in positions:  # 按顺序处理每一块掉落的方块，解包出左边界与边长
            r = l + w - 1  # 边长 w 的方块占据的右边界（左闭右闭）
            h = tree.query(l, r) + w  # 落在 [l, r] 最高处之上，再加自身边长，得到本块顶部高度
            mx = max(mx, h)  # 用本块顶部高度更新全局最高高度
            ans.append(mx)  # 本题要求输出的是当前全局最大值，而非本块自身高度
            tree.modify(l, r, h)  # 把 [l, r] 这一整段的高度更新为本块顶部高度
        return ans  # 返回每块方块落下后的全局最高高度序列
