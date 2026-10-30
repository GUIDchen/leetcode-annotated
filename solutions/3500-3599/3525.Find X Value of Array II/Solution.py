# 题目：3525. 求出数组的 X 值 II（Find X Value of Array II）
# 思路：线段树维护每段的「整段乘积 mod k」与「各前缀积余数的个数」。合并时左段前缀原样保留，右段前缀整体乘上左段乘积；答案即后缀 [start, n-1] 前缀分布中 x 的计数。
# 时间复杂度：O((n + q·log n)·k)，建树 O(n·k)、每次查询/修改 O(k·log n)；空间复杂度：O(n·k)。
class Node:  # 线段树节点：区间边界 + 整段乘积 + 前缀余数分布
    __slots__ = "l", "r", "prod", "cnt"  # 用 __slots__ 省内存并加快属性访问

    def __init__(self, l: int, r: int, k: int):  # 节点构造：区间 [l, r] 与模数 k
        self.l = l  # 区间左端点（1-based）
        self.r = r  # 区间右端点
        self.prod = 1  # 整段所有元素乘积模 k 后的余数
        self.cnt = [0] * k  # cnt[r] 表示前缀积模 k 余 r 的前缀个数


class SegmentTree:  # 支持单点修改与区间查询的线段树
    __slots__ = "k", "tr"  # 只保留模数与节点数组两个属性

    def __init__(self, nums: list[int], k: int):  # 用原数组与模数 k 建树
        self.k = k  # 保存模数，供 merge/modify/build 使用
        n = len(nums)  # 数组长度，线段树下标为 1..n
        self.tr = [None] * (n << 2)  # 4n 个槽位足够覆盖整棵树
        self.build(1, 1, n, nums)  # 从根节点递归建树

    def merge(self, a: Node, b: Node) -> tuple[int, list[int]]:  # 把左段 a 与右段 b 合并，返回 (整段乘积, 前缀分布)
        k = self.k  # 取出模数
        prod = a.prod * b.prod % k  # 整段乘积 = 左段乘积 × 右段乘积（取模）
        cnt = a.cnt[:]  # a 自身的前缀仍然是合并区间的前缀，先拷贝过来
        for r, c in enumerate(b.cnt):  # 枚举右段每种前缀积余数 r 及其个数 c
            cnt[a.prod * r % k] += c  # 「整个 a + b 的前缀」余数整体乘上 a.prod
        return prod, cnt  # 返回合并后的整段乘积与前缀分布

    def pushup(self, u: int):  # 用左右儿子刷新节点 u
        prod, cnt = self.merge(self.tr[u << 1], self.tr[u << 1 | 1])  # 先合并左右两个儿子
        self.tr[u].prod = prod  # 更新父节点的整段乘积
        self.tr[u].cnt = cnt  # 更新父节点的前缀余数分布

    def build(self, u: int, l: int, r: int, nums: list[int]):  # 以 u 为根，递归建出区间 [l, r]
        self.tr[u] = Node(l, r, self.k)  # 先为节点分配对象
        if l == r:  # 叶子节点，区间只含一个元素
            v = nums[l - 1] % self.k  # 取该元素并取模（数组下标为 0-based）
            self.tr[u].prod = v  # 单元素区间的乘积就是它本身
            self.tr[u].cnt[v] = 1  # 只有一个前缀，余数为 v
            return  # 叶子建完直接返回
        mid = (l + r) >> 1  # 取中点划分左右子区间
        self.build(u << 1, l, mid, nums)  # 递归建立左子树
        self.build(u << 1 | 1, mid + 1, r, nums)  # 递归建立右子树
        self.pushup(u)  # 由两个儿子合并出当前节点

    def modify(self, u: int, x: int, v: int):  # 把下标 x 处的元素改成 v
        if self.tr[u].l == self.tr[u].r:  # 走到叶子，只剩被修改的那一个位置
            v %= self.k  # 只需保留余数，后续运算都在模 k 下进行
            self.tr[u].prod = v  # 单元素区间的乘积就是它自己
            self.tr[u].cnt = [0] * self.k  # 清空旧的前缀余数分布
            self.tr[u].cnt[v] = 1  # 该元素本身是唯一的前缀，余数为 v
            return  # 叶子处理完直接返回
        mid = (self.tr[u].l + self.tr[u].r) >> 1  # 取中点，判断目标在左还是右
        if x <= mid:  # 目标位置在左子树
            self.modify(u << 1, x, v)  # 递归修改左儿子
        else:  # 目标位置在右子树
            self.modify(u << 1 | 1, x, v)  # 递归修改右儿子
        self.pushup(u)  # 儿子都更新完了，重新合并出父节点的信息

    def query(self, u: int, l: int, r: int) -> Node:  # 查询闭区间 [l, r] 合并后的节点信息
        if self.tr[u].l >= l and self.tr[u].r <= r:  # 当前节点被查询区间完全覆盖
            return self.tr[u]  # 整段信息可以直接返回
        mid = (self.tr[u].l + self.tr[u].r) >> 1  # 取中点，判断查询区间落在哪一侧
        if r <= mid:  # 查询区间只落在左子树
            return self.query(u << 1, l, r)  # 全部交给左儿子
        if l > mid:  # 查询区间只落在右子树
            return self.query(u << 1 | 1, l, r)  # 全部交给右儿子
        left = self.query(u << 1, l, r)  # 区间跨过中点：先查左半区间
        right = self.query(u << 1 | 1, l, r)  # 再查右半区间
        prod, cnt = self.merge(left, right)  # 左右两段按顺序拼接成一个整体
        res = Node(0, 0, self.k)  # 新建一个节点承载合并结果
        res.prod = prod  # 写入整段乘积
        res.cnt = cnt  # 写入前缀余数分布
        return res  # 返回合并后的节点


class Solution:  # LeetCode 约定的题解类
    def resultArray(  # 方法签名跨行书写，参数依次为 nums、k、queries
        self, nums: list[int], k: int, queries: list[list[int]]  # 续行：形参及其类型
    ) -> list[int]:  # 返回每个查询的答案
        n = len(nums)  # 数组长度
        tree = SegmentTree(nums, k)  # 用初始 nums 建线段树
        ans = []  # 保存每个查询的答案
        for idx, val, start, x in queries:  # 依次处理每个查询 [下标, 新值, 起点, 目标余数]
            tree.modify(1, idx + 1, val)  # 先把 nums[idx] 改成 val（下标转成 1-based）
            ans.append(tree.query(1, start + 1, n).cnt[x])  # 查询后缀 [start, n-1] 中前缀积余数为 x 的个数
        return ans  # 返回所有查询的答案
