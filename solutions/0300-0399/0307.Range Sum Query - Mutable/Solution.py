# 题目：307. 区域和检索 - 数组可修改（Range Sum Query - Mutable）
# 思路：树状数组维护前缀和，单点修改与前缀查询都是 O(log n)，区间和由两个前缀和相减。
# 时间复杂度：构造 O(n log n)、更新 O(log n)、查询 O(log n)；空间复杂度：O(n)，树状数组本体。
class BinaryIndexedTree:  # 树状数组：单点加 + 前缀和查询
    __slots__ = ["n", "c"]  # 用 __slots__ 限定属性，省内存也略快

    def __init__(self, n):  # 构造函数：n 为数据规模
        self.n = n  # 记录长度
        self.c = [0] * (n + 1)  # 树状数组本体，1 基下标，多开一位

    def update(self, x: int, delta: int):  # 在下标 x 处加 delta（1 基下标）
        while x <= self.n:  # 沿 lowbit 链向上，更新覆盖 x 的所有节点
            self.c[x] += delta  # 当前节点累加增量
            x += x & -x  # 跳到下一个覆盖该点的节点

    def query(self, x: int) -> int:  # 查询前缀和 [1, x]
        s = 0  # 累加器
        while x > 0:  # 沿 lowbit 链向下，把各段拼成完整前缀
            s += self.c[x]  # 累加当前节点的区间和
            x -= x & -x  # 去掉最低位的 1，跳到前一段
        return s  # 返回前缀和


class NumArray:  # LeetCode 约定的题解类
    __slots__ = ["tree"]  # 用 __slots__ 只保留 tree 一个属性

    def __init__(self, nums: List[int]):  # 构造函数：nums 是初始数组
        self.tree = BinaryIndexedTree(len(nums))  # 建树状数组
        for i, v in enumerate(nums, 1):  # 从 1 开始编号，正好符合树状数组的 1 基下标
            self.tree.update(i, v)  # 逐个插入元素

    def update(self, index: int, val: int) -> None:  # 把下标 index 处的值改为 val
        prev = self.sumRange(index, index)  # 先求原值（单点查询 = 两个前缀和相减）
        self.tree.update(index + 1, val - prev)  # 只更新差值即可

    def sumRange(self, left: int, right: int) -> int:  # 查询闭区间 [left, right] 的和
        return self.tree.query(right + 1) - self.tree.query(left)  # 前缀和相减即得区间和


# Your NumArray object will be instantiated and called as such:
# obj = NumArray(nums)
# obj.update(index,val)
# param_2 = obj.sumRange(left,right)
