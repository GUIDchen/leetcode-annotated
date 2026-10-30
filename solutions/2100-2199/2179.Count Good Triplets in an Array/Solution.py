# 题目：2179. 统计数组中好三元组数目（Count Good Triplets in an Array）
# 思路：以元素在 nums2 中的下标作为位置，按 nums1 的顺序插入树状数组；每个元素可配出的好三元组数等于「左侧已出现个数 × 右侧尚未出现个数」。
# 时间复杂度：O(n log n)，每个元素两次查询加一次更新；空间复杂度：O(n)，位置字典与树状数组。
class BinaryIndexedTree:  # 树状数组（Fenwick 树）：支持单点加值与前缀和查询
    def __init__(self, n):  # n：下标范围是 1 ~ n
        self.n = n  # 记录下标上界
        self.c = [0] * (n + 1)  # 树状数组本体，多开一位让下标从 1 开始

    @staticmethod  # 静态方法：不需要访问实例状态
    def lowbit(x):  # 取 x 二进制最低位的 1 所代表的值
        return x & -x  # 位运算实现：x 与 -x 相与

    def update(self, x, delta):  # 单点更新：把位置 x 增加 delta
        while x <= self.n:  # 沿 lowbit 向上更新所有管辖 x 的节点
            self.c[x] += delta  # 该节点维护的区间和增加 delta
            x += BinaryIndexedTree.lowbit(x)  # 跳到下一个管辖当前区间的节点

    def query(self, x):  # 前缀和查询：返回位置 1 ~ x 的元素之和
        s = 0  # 累加答案
        while x > 0:  # 沿 lowbit 向下累加各段区间
            s += self.c[x]  # 累加当前节点维护的区间和
            x -= BinaryIndexedTree.lowbit(x)  # 跳到前面的区间
        return s  # 返回 1 ~ x 的前缀和


class Solution:  # LeetCode 约定的题解类
    def goodTriplets(self, nums1: List[int], nums2: List[int]) -> int:  # nums1、nums2：两个长度为 n 的 0 ~ n-1 的排列
        pos = {v: i for i, v in enumerate(nums2, 1)}  # pos[v]：值 v 在 nums2 中的位置（1 基，便于树状数组）
        ans = 0  # 好三元组的个数
        n = len(nums1)  # 排列长度，也是树状数组的大小
        tree = BinaryIndexedTree(n)  # 树状数组统计已经出现过的位置
        for num in nums1:  # 按 nums1 的顺序依次插入元素
            p = pos[num]  # 当前元素在 nums2 中的位置
            left = tree.query(p)  # 已遍历过且位置比 p 靠前的元素个数，可作为三元组的左端点
            right = n - p - (tree.query(n) - tree.query(p))  # 位置比 p 靠后且尚未被遍历到的元素个数，可作为三元组的右端点
            ans += left * right  # 以当前元素为中点，左右各选一个即构成好三元组
            tree.update(p, 1)  # 把当前元素的位置标记为已出现
        return ans  # 返回好三元组的总数
