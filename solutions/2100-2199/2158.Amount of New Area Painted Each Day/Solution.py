# 题目：2158. 每天绘制新区域的数量（Amount of New Area Painted Each Day）
# 核心思路：线段树维护区间被覆盖的长度；每天先查询该区间已覆盖多少，用区间长度减去它得到新增面积，再把整段置为已覆盖。
# 时间复杂度：O(n log V)，V 为坐标值域；空间复杂度：O(V)，线段树节点按需创建。
class Node:  # 线段树节点
    def __init__(self, l, r):  # 构造一个覆盖 [l, r] 的节点
        self.left = None  # 左子节点，用到时再创建
        self.right = None  # 右子节点，用到时再创建
        self.l = l  # 区间左端点
        self.r = r  # 区间右端点
        self.mid = (l + r) >> 1  # 区间中点，用来划分左右子节点
        self.v = 0  # 该区间内已被覆盖的长度
        self.add = 0  # 懒标记：非 0 表示整段被覆盖，取值是覆盖状态


class SegmentTree:  # 支持区间置覆盖与区间查询覆盖长度的线段树
    def __init__(self):  # 构造函数：建立一棵空线段树
        self.root = Node(1, 10**5 + 10)  # 坐标从 1 开始，开到 10**5 + 10 覆盖题目坐标范围

    def modify(self, l, r, v, node=None):  # 把区间 [l, r] 的覆盖状态改成 v；node 为 None 表示入口调用
        if l > r:  # 空区间
            return  # 直接返回
        if node is None:  # 没指定节点说明这是入口调用
            node = self.root  # 从根节点开始递归
        if node.l >= l and node.r <= r:  # 当前节点区间被目标区间完全包含
            node.v = node.r - node.l + 1  # 整段都被覆盖，覆盖长度等于区间长度
            node.add = v  # 打上懒标记，标记这次整体覆盖的状态
            return  # 结束本层递归
        self.pushdown(node)  # 部分覆盖，先把父节点的懒标记下传给子节点
        if l <= node.mid:  # 左半区间与目标区间有交集
            self.modify(l, r, v, node.left)  # 递归修改左子节点
        if r > node.mid:  # 右半区间与目标区间有交集
            self.modify(l, r, v, node.right)  # 递归修改右子节点
        self.pushup(node)  # 由子节点的覆盖长度更新当前节点

    def query(self, l, r, node=None):  # 查询区间 [l, r] 已被覆盖的长度；node 为 None 表示入口调用
        if l > r:  # 空区间
            return 0  # 没有覆盖长度
        if node is None:  # 没指定节点说明这是入口调用
            node = self.root  # 从根节点开始递归
        if node.l >= l and node.r <= r:  # 当前节点区间被查询区间完全包含
            return node.v  # 直接返回该节点记录的覆盖长度
        self.pushdown(node)  # 要访问子节点，先把懒标记下传
        v = 0  # 覆盖长度累加器
        if l <= node.mid:  # 左半区间有交集
            v += self.query(l, r, node.left)  # 累加左子树的覆盖长度
        if r > node.mid:  # 右半区间有交集
            v += self.query(l, r, node.right)  # 累加右子树的覆盖长度
        return v  # 返回查询区间内的总覆盖长度

    def pushup(self, node):  # 由子节点信息向上更新
        node.v = node.left.v + node.right.v  # 父区间的覆盖长度等于左右子区间覆盖长度之和

    def pushdown(self, node):  # 把当前节点的懒标记下传给子节点
        if node.left is None:  # 左子节点还没创建
            node.left = Node(node.l, node.mid)  # 按左半区间创建左子节点
        if node.right is None:  # 右子节点还没创建
            node.right = Node(node.mid + 1, node.r)  # 按右半区间创建右子节点
        if node.add:  # 只有存在懒标记时才需要下传
            left, right = node.left, node.right  # 同时取出左右子节点，方便书写
            left.v = left.r - left.l + 1  # 左子区间被整段覆盖，覆盖长度等于其区间长度
            right.v = right.r - right.l + 1  # 右子区间被整段覆盖，覆盖长度等于其区间长度
            left.add = node.add  # 标记传给左子节点
            right.add = node.add  # 标记传给右子节点
            node.add = 0  # 清空当前节点的标记，避免重复下传


class Solution:  # LeetCode 约定的题解类
    def amountPainted(self, paint: List[List[int]]) -> List[int]:  # paint[i] = [start, end) 是第 i 天刷墙的区间
        tree = SegmentTree()  # 新建一棵全未覆盖的线段树
        ans = []  # 记录每天新增的绘制长度
        for i, (start, end) in enumerate(paint):  # 按天依次处理，取出左右端点
            l, r = start + 1, end  # 原区间左闭右开，线段树下标从 1 起，故左端点加一
            v = tree.query(l, r)  # 先查询这段区间里已经被刷过的长度
            ans.append(r - l + 1 - v)  # 区间总长减去已覆盖长度，就是今天新增的面积
            tree.modify(l, r, 1)  # 把今天的区间标记为已覆盖，供后面几天查询
        return ans  # 返回每天的答案
