# 题目：2426. 满足不等式的数对数目（Number of Pairs Satisfying Inequality）
# 核心思路：条件等价于 nums1[i]-nums2[i] <= nums1[j]-nums2[j] + diff。令 v = nums1-nums2，按下标顺序扫描，用树状数组统计已出现过的 v，对当前 v 查询有多少旧值 <= v+diff；下标统一 +40000 平移以消掉负数。
# 时间复杂度：O(n log C)，C 为值域 1e5；空间复杂度：O(C)，即树状数组的存储开销。
class BinaryIndexedTree:  # 树状数组：单点加 + 前缀和查询
    def __init__(self, n):  # 构造函数，n 为值域上界
        self.n = n  # 记录值域上界，供 update 判断边界
        self.c = [0] * (n + 1)  # 下标 1..n 有效，多开一格恰好容纳下标 n

    @staticmethod  # 静态方法：lowbit 只依赖参数，不需要实例状态
    def lowbit(x):  # 取出 x 最低位 1 所代表的数值
        return x & -x  # 位运算技巧：x & -x 只保留下最低位的 1

    def update(self, x, delta):  # 在下标 x 处把计数增加 delta
        while x <= self.n:  # 未越界时沿父节点方向向上更新
            self.c[x] += delta  # 更新当前节点维护的区间和
            x += BinaryIndexedTree.lowbit(x)  # 跳到下一个覆盖 x 的节点

    def query(self, x):  # 查询前缀 [1, x] 的元素总数
        s = 0  # 前缀和累加器
        while x:  # x 为 0 时循环结束（即前缀已累加完）
            s += self.c[x]  # 累加当前节点覆盖的区间
            x -= BinaryIndexedTree.lowbit(x)  # 剥离最低位 1，继续处理剩余前缀
        return s  # 返回 [1, x] 的计数和


class Solution:  # LeetCode 约定的题解类
    def numberOfPairs(self, nums1: List[int], nums2: List[int], diff: int) -> int:  # nums1、nums2 是输入数组，diff 是允许的偏差
        tree = BinaryIndexedTree(10**5)  # 值域取 1e5，足以容纳平移后的所有 v 值
        ans = 0  # 满足不等式的下标对计数
        for a, b in zip(nums1, nums2):  # 按顺序同时取出两数组元素，当前下标当作 j，树状数组里只有 i < j 的旧值
            v = a - b  # 条件变形后的值 v_j = a - b
            ans += tree.query(v + diff + 40000)  # 统计旧值中满足 v_i <= v_j + diff 的个数，+40000 用于消除负数下标
            tree.update(v + 40000, 1)  # 把当前 v_j 记入树状数组，供后面的下标使用
        return ans  # 返回满足不等式的数对总数
