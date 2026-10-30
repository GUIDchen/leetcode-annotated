# 题目：2213. 由单个字符重复的最长子字符串（Longest Substring of One Repeating Character）
# 思路：线段树每个节点维护左端起 lmx、右端起 rmx 与区间最长 mx，单点修改后逐层 pushup，根节点 mx 即答案。
# 时间复杂度：O((n + k) log n)，建树 O(n)、每次修改 O(log n)；空间复杂度：O(n)，节点数组开 4n。
def max(a: int, b: int) -> int:  # 自定义 max：保证比较逻辑与类型标注一致
    return a if a > b else b  # 三元表达式：a 更大返回 a，否则返回 b


class Node:  # 线段树节点：记录区间端点以及该区间的三种最长同字符长度
    __slots__ = "l", "r", "lmx", "rmx", "mx"  # 用 __slots__ 固定属性名，减少每个节点的内存开销

    def __init__(self, l: int, r: int):  # 初始化节点：给定区间 [l, r]
        self.l = l  # 记录左端点
        self.r = r  # 记录右端点
        self.lmx = self.rmx = self.mx = 1  # 单点区间的最长同字符长度至少为 1


class SegmentTree:  # 线段树：支持单点修改，并维护全局最长同字符子串
    __slots__ = "s", "tr"  # 固定属性：字符列表 s 与节点数组 tr

    def __init__(self, s: str):  # 构造函数：用字符串 s 建树
        self.s = list(s)  # 转成列表，因为后面需要按下标修改字符
        n = len(s)  # n 是串长，节点下标使用 [1, n]
        self.tr: List[Node | None] = [None] * (n * 4)  # 4n 容量的节点数组，None 表示尚未创建
        self.build(1, 1, n)  # 从根节点 1 开始建整棵树

    def build(self, u: int, l: int, r: int):  # 递归建树：为区间 [l, r] 创建编号为 u 的节点
        self.tr[u] = Node(l, r)  # 创建当前节点并登记它负责的区间
        if l == r:  # 叶子节点：区间里只剩一个字符
            return  # 叶子无需继续递归，直接返回
        mid = (l + r) // 2  # 取中点把区间一分为二
        self.build(u << 1, l, mid)  # 递归建左子树 [l, mid]
        self.build(u << 1 | 1, mid + 1, r)  # 递归建右子树 [mid + 1, r]
        self.pushup(u)  # 子树就绪后，合并信息到当前节点

    def query(self, u: int, l: int, r: int) -> int:  # 区间查询：返回 [l, r] 内的最长同字符长度
        if self.tr[u].l >= l and self.tr[u].r <= r:  # 当前节点区间被查询区间完全覆盖，直接返回缓存的 mx
            return self.tr[u].mx  # 直接命中答案
        mid = (self.tr[u].l + self.tr[u].r) // 2  # 取中点，判断查询区间落在哪一侧
        ans = 0  # 答案初值 0，等待子区间结果来更新
        if r <= mid:  # 查询区间完全落在左半边
            ans = self.query(u << 1, l, r)  # 只查左子树
        if l > mid:  # 查询区间完全落在右半边
            ans = max(ans, self.query(u << 1 | 1, l, r))  # 与已有答案取较大者
        return ans  # 返回区间内的最长重复长度

    def modify(self, u: int, x: int, v: str):  # 单点修改：把 1-based 下标 x 处的字符改成 v
        if self.tr[u].l == self.tr[u].r:  # 走到叶子说明定位到了目标位置
            self.s[x - 1] = v  # 真正写入新字符（内部下标从 0 开始，所以减 1）
            return  # 叶子无需合并，回溯
        mid = (self.tr[u].l + self.tr[u].r) // 2  # 按中点判断递归方向
        if x <= mid:  # 目标在左半区间
            self.modify(u << 1, x, v)  # 递归修改左子树
        else:  # 否则目标在右半区间
            self.modify(u << 1 | 1, x, v)  # 递归修改右子树
        self.pushup(u)  # 子树变化后，重新合并当前节点

    def pushup(self, u: int):  # 合并：用左右儿子刷新当前节点的三种长度
        root, left, right = self.tr[u], self.tr[u << 1], self.tr[u << 1 | 1]  # 一次取出当前节点与它的左右儿子
        root.lmx = left.lmx  # 左端起长度默认继承左儿子
        root.rmx = right.rmx  # 右端起长度默认继承右儿子
        root.mx = max(left.mx, right.mx)  # 区间最大值至少是左右儿子最大值的较大者
        a, b = left.r - left.l + 1, right.r - right.l + 1  # a、b 分别是左右儿子的区间长度，用于判断是否整段同字符
        if self.s[left.r - 1] == self.s[right.l - 1]:  # 仅当交界两侧字符相同，才可能跨区间拼接
            if left.lmx == a:  # 左儿子整段同字符，左前缀才能继续向右延伸
                root.lmx += right.lmx  # 左端起长度 = 左儿子全长 + 右儿子的左前缀
            if right.rmx == b:  # 右儿子整段同字符，右后缀才能继续向左延伸
                root.rmx += left.rmx  # 右端起长度 = 右儿子全长 + 左儿子的右后缀
            root.mx = max(root.mx, left.rmx + right.lmx)  # 跨交界长度 = 左儿子后缀 + 右儿子前缀，与已有最大值取较大者


class Solution:  # LeetCode 约定的题解类
    def longestRepeating(  # s 为初始串；queryCharacters 是替换字符；queryIndices 是替换位置
        self, s: str, queryCharacters: str, queryIndices: List[int]  # 形参续行：原串、替换字符序列、替换下标序列
    ) -> List[int]:  # 返回每次替换后整个串的最长同字符长度
        tree = SegmentTree(s)  # 用初始字符串建树
        ans = []  # 答案列表，按修改顺序累积结果
        for x, v in zip(queryIndices, queryCharacters):  # 同时取出本次的下标 x 与新字符 v
            tree.modify(1, x + 1, v)  # 线段树内部下标从 1 开始，因此把 x 加 1
            ans.append(tree.query(1, 1, len(s)))  # 根节点 mx 就是全局最长重复长度
        return ans  # 返回全部答案
