# 题目：3161. 物块放置查询（Block Placement Queries）
# 核心思路：倒序处理操作，把「放置障碍」化为「删除障碍」；SortedList 维护障碍坐标，树状数组维护各障碍右端的最大区间长度，询问时比较左侧最大区间与 prev..x 这段是否够长。
# 时间复杂度：O((n+m)log m)，SortedList 与树状数组操作均为对数级；空间复杂度：O(m)，树状数组大小由坐标上界决定。
class BinaryIndexedTree:  # 树状数组：单点取 max 更新 + 前缀最大值查询
    def __init__(self, n: int):  # n 为坐标上界
        self.n = n  # 记下上界，update 循环要用
        self.c = [0] * (n + 1)  # 开 n+1 个桶，下标 1..n

    def update(self, x: int, v: int):  # 在位置 x 上用 v 更新最大值
        while x <= self.n:  # 沿 lowbit 向上，覆盖所有包含 x 的区间
            self.c[x] = max(self.c[x], v)  # 区间取 max
            x += x & -x  # x + lowbit(x) 跳到父节点

    def query(self, x: int) -> int:  # 查询前缀 [1, x] 的最大值
        mx = 0  # 区间长度非负，用 0 初始化
        while x:  # 沿 lowbit 向下把前缀拆成若干块
            mx = max(mx, self.c[x])  # 用当前块更新答案
            x -= x & -x  # 跳到前一块
        return mx  # 返回前缀最大值


class Solution:  # LeetCode 约定的题解类
    def getResults(self, queries: List[List[int]]) -> List[bool]:  # queries：q[0]=1 放置障碍，q[0]=2 询问能否放下长 q[2] 的物块
        m = max(q[1] for q in queries)  # 所有操作中的最大坐标
        sl = SortedList([0, m + 1])  # 障碍坐标有序集合，额外放哨兵 0 与 m+1，保证每段都有两个端点
        for q in queries:  # 先收集全部障碍
            if q[0] == 1:  # 只有类型 1 才放置障碍
                sl.add(q[1])  # 记录障碍坐标
        tree = BinaryIndexedTree(m + 1)  # 以坐标上界建树状数组
        for x1, x2 in pairwise(sl):  # 相邻两个障碍构成一个可用区间
            tree.update(x2, x2 - x1)  # 把区间长度挂到右端点 x2 上
        ans = []  # 逆序处理时暂存答案
        for q in reversed(queries):  # 倒序撤销操作，从最终状态往回退
            x = q[1]  # 当前操作的坐标
            if q[0] == 1:  # 倒序遇到放置 = 删除该障碍
                i = sl.index(x)  # 找到它在有序集合中的下标
                tree.update(sl[i + 1], sl[i + 1] - sl[i - 1])  # 删除后左右两段合并，更新右端点的最大长度
                sl.remove(x)  # 从集合中移除该障碍
            else:  # 询问：此时集合恰好是询问发生之前的状态
                i = sl.bisect_right(x)  # 找 x 右侧第一个障碍的位置
                pre = sl[i - 1]  # x 左边最近的障碍
                ans.append(tree.query(pre) >= q[2] or x - pre >= q[2])  # 左侧已有够长区间，或 prev..x 这段够长，都说明放得下
        return ans[::-1]  # 逆序收集的答案翻转回正序返回
