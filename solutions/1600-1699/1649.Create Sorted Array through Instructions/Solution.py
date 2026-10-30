# 题目：1649. 通过指令创建有序数组（Create Sorted Array through Instructions）
# 思路：树状数组统计已插入值的出现次数；处理 x 时左侧严格小的个数是 query(x-1)，右侧严格大的个数是 i - query(x)，取较小者累加。
# 时间复杂度：O(n log m)，m 为最大值；空间复杂度：O(m)，树状数组需要 m+1 个桶。
class BinaryIndexedTree:  # 树状数组：O(log m) 单点加与前缀和
    def __init__(self, n):  # 构造函数：n 为值域上界
        self.n = n  # 保存上界，供 update 判越界
        self.c = [0] * (n + 1)  # 1-based 开 n+1 个桶，下标 0 空置

    def update(self, x: int, v: int):  # 在下标 x 处加 v
        while x <= self.n:  # 沿 lowbit 向上更新覆盖 x 的节点
            self.c[x] += v  # 当前节点累加 v
            x += x & -x  # x += lowbit(x) 跳到下一个覆盖位置

    def query(self, x: int) -> int:  # 查询前缀和 1..x
        s = 0  # 累加器
        while x:  # x 减到 0 时结束
            s += self.c[x]  # 累加当前区间的计数
            x -= x & -x  # x -= lowbit(x) 跳到前一个区间
        return s  # 返回前缀和


class Solution:  # LeetCode 约定的题解类
    def createSortedArray(self, instructions: List[int]) -> int:  # instructions 是插入序列，返回每次插入最小代价之和（取模）
        m = max(instructions)  # 值域上界取最大值
        tree = BinaryIndexedTree(m)  # 建立树状数组
        ans = 0  # 累计代价
        mod = 10**9 + 7  # 取模常量
        for i, x in enumerate(instructions):  # i 是此前已插入的个数，x 是当前值
            cost = min(tree.query(x - 1), i - tree.query(x))  # 左严格小 query(x-1) 与右严格大 i-query(x) 取较小
            ans += cost  # 累加本次代价
            tree.update(x, 1)  # 把 x 的计数加一
        return ans % mod  # 最后统一取模返回
