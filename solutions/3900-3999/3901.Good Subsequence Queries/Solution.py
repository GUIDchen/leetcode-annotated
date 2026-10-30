# 3901. 好子序列查询 / Good Subsequence Queries
# 核心思路：线段树维护「p 的倍数」的区间 gcd。整体 gcd 不等于 p 时必无解；否则若存在非 p 的倍数（可直接剔除）或元素足够多则有解，全部为 p 的倍数时枚举删除哪个元素并检查剩余部分的 gcd。
# 复杂度：时间 O((n + q log n) + q·n log n)（仅 n <= 6 时枚举），空间 O(n)。
class Node:  # 线段树节点：区间 [l, r] 与其中「p 的倍数」的 gcd
    __slots__ = "l", "r", "g"  # 限定属性，节省内存

    def __init__(self, l: int, r: int):  # 构造函数
        self.l = l  # 区间左端点
        self.r = r  # 区间右端点
        self.g = 0  # gcd 的幺元取 0


class SegmentTree:  # 维护区间 gcd 的线段树
    __slots__ = "tr"  # 限定属性

    def __init__(self, n: int):  # 以 [1, n] 建树
        self.tr: list[Node | None] = [None] * (n << 2)  # 节点池开 4n 个位置
        self.build(1, 1, n)  # 从根节点递归建树

    def build(self, u: int, l: int, r: int):  # 为节点 u 建立管辖区间 [l, r]
        self.tr[u] = Node(l, r)  # 新建节点
        if l == r:  # 到达叶子节点
            return  # 叶子直接返回
        mid = (l + r) >> 1  # 区间中点
        self.build(u << 1, l, mid)  # 递归建立左子树
        self.build(u << 1 | 1, mid + 1, r)  # 递归建立右子树

    def pushup(self, u: int):  # 用左右儿子的 gcd 更新当前节点
        self.tr[u].g = gcd(self.tr[u << 1].g, self.tr[u << 1 | 1].g)  # 父区间 gcd 等于两子区间 gcd 的 gcd

    def modify(self, u: int, x: int, v: int):  # 把位置 x 上的值改为 v
        if self.tr[u].l == self.tr[u].r:  # 找到叶子节点
            self.tr[u].g = v  # 直接覆盖为 v
            return  # 回溯
        mid = (self.tr[u].l + self.tr[u].r) >> 1  # 当前区间的中点
        if x <= mid:  # 位置落在左子树
            self.modify(u << 1, x, v)  # 递归修改左子树
        else:  # 位置落在右子树
            self.modify(u << 1 | 1, x, v)  # 递归修改右子树
        self.pushup(u)  # 回溯时更新当前节点的 gcd

    def query(self, u: int, l: int, r: int) -> int:  # 查询区间 [l, r] 的 gcd
        if l > r:  # 空区间
            return 0  # 空区间的 gcd 取幺元 0
        if self.tr[u].l >= l and self.tr[u].r <= r:  # 当前节点区间被完全覆盖
            return self.tr[u].g  # 直接返回该节点的 gcd
        mid = (self.tr[u].l + self.tr[u].r) >> 1  # 当前区间的中点
        if r <= mid:  # 查询区间只在左子树
            return self.query(u << 1, l, r)  # 递归查询左子树
        if l > mid:  # 查询区间只在右子树
            return self.query(u << 1 | 1, l, r)  # 递归查询右子树
        return gcd(self.query(u << 1, l, mid), self.query(u << 1 | 1, mid + 1, r))  # 跨越中点，合并左右两段的 gcd


class Solution:  # 题解类
    def countGoodSubseq(self, nums: list[int], p: int, queries: list[list[int]]) -> int:  # nums 为数组，p 为目标 gcd，queries 为单点修改；返回存在好子序列的查询个数
        n = len(nums)  # 数组长度
        tree = SegmentTree(n)  # 建立维护区间 gcd 的线段树
        cnt = 0  # 记录 p 的倍数在数组中的个数

        for i, x in enumerate(nums, 1):  # 按初值建树，位置从 1 开始
            if x % p == 0:  # 只有 p 的倍数才可能进入好子序列
                tree.modify(1, i, x)  # 写入该位置的值
                cnt += 1  # 倍数计数加一

        ans = 0  # 统计存在好子序列的查询个数
        for idx, val in queries:  # 依次处理每个查询
            if nums[idx] % p == 0:  # 旧值原本是 p 的倍数
                tree.modify(1, idx + 1, 0)  # 从线段树中清除旧值
                cnt -= 1  # 倍数计数减一
            if val % p == 0:  # 新值是 p 的倍数
                tree.modify(1, idx + 1, val)  # 把新值写入线段树
                cnt += 1  # 倍数计数加一
            nums[idx] = val  # 同步更新原数组

            if tree.tr[1].g != p:  # 整体 gcd 不等于 p，任何子序列都不可能满足
                continue  # 本次查询无解，直接跳过

            if cnt < n or n > 6:  # 存在非 p 的倍数（可整体删去）或元素足够多时，好子序列必定存在
                ans += 1  # 本次查询计入答案
                continue  # 处理下一个查询

            for i in range(1, n + 1):  # 全部都是 p 的倍数时，枚举被删掉的那个元素
                left_g = tree.query(1, 1, i - 1)  # 删掉 i 后左半段的 gcd
                right_g = tree.query(1, i + 1, n)  # 删掉 i 后右半段的 gcd
                if gcd(left_g, right_g) == p:  # 剩余元素的 gcd 仍等于 p
                    ans += 1  # 本次查询计入答案
                    break  # 每个查询最多计一次

        return ans  # 返回答案
