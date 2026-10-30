# 题目：315. 计算右侧小于当前元素的个数（Count of Smaller Numbers After Self）
# 思路：把所有值离散化后用树状数组维护出现次数，从右往左扫描，边插入边查询严格小于当前值的个数。
# 时间复杂度：O(n log n)，每次更新与查询都是 O(log n)；空间复杂度：O(n)，离散化表与树状数组。
class BinaryIndexedTree:  # 树状数组（Fenwick 树）：支持单点加、前缀和查询
    def __init__(self, n):  # n：离散化后的元素个数
        self.n = n  # 记录规模
        self.c = [0] * (n + 1)  # 下标从 1 开始，长度 n + 1，初始全 0

    @staticmethod  # 静态方法，不需要访问实例
    def lowbit(x):  # 取出 x 二进制最低位的 1
        return x & -x  # 位运算技巧：x & -x

    def update(self, x, delta):  # 在位置 x 上加上 delta
        while x <= self.n:  # 沿父节点链向上更新
            self.c[x] += delta  # 把增量累加到当前节点
            x += BinaryIndexedTree.lowbit(x)  # 跳到下一个需要更新的节点

    def query(self, x):  # 求前缀和 1..x
        s = 0  # 累加器，保存前缀和
        while x > 0:  # 沿前一个块链向下累加
            s += self.c[x]  # 加上当前块覆盖的区间和
            x -= BinaryIndexedTree.lowbit(x)  # 跳到左边剩下的区间
        return s  # 返回前缀和


class Solution:  # LeetCode 约定的题解类
    def countSmaller(self, nums: List[int]) -> List[int]:  # nums：待统计的数组
        alls = sorted(set(nums))  # 去重并升序排序，用于离散化
        m = {v: i for i, v in enumerate(alls, 1)}  # 值 → 离散化后的下标（enumerate 从 1 开始计数）
        tree = BinaryIndexedTree(len(m))  # 按不同值个数建树状数组
        ans = []  # 按从右往左的顺序记录答案
        for v in nums[::-1]:  # 逆序遍历，保证树中只有当前元素右侧的数
            x = m[v]  # 当前值离散化后的下标
            tree.update(x, 1)  # 把当前值计入树状数组
            ans.append(tree.query(x - 1))  # 统计严格小于当前值的个数
        return ans[::-1]  # 反转回原始顺序
