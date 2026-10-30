# 题目：3187. 数组中的峰值（Peaks in Array）
# 思路：用树状数组维护每个下标「是否为峰」的 0/1 标记；查询时对区间 [q1+1, q2-1] 求前缀和之差，修改时只重算 idx-1、idx、idx+1 三处。
# 时间复杂度：O((n + q) log n)，每次操作都是对数级；空间复杂度：O(n)，树状数组长度为 n+1。
class BinaryIndexedTree:  # 树状数组：单点增减与前缀和查询都是 O(log n)
    __slots__ = "n", "c"  # 限定实例属性名，省内存并避免拼写错误

    def __init__(self, n: int):  # 构造函数：n 是允许使用的最大下标
        self.n = n  # 保存下标上界
        self.c = [0] * (n + 1)  # 多开一位，让下标从 1 开始，方便 lowbit 计算

    def update(self, x: int, delta: int) -> None:  # 把下标 x 对应的值增加 delta
        while x <= self.n:  # 沿 lowbit 向上更新所有覆盖 x 的节点
            self.c[x] += delta  # 累加这次增量
            x += x & -x  # 跳到父节点

    def query(self, x: int) -> int:  # 求 1..x 的前缀和
        s = 0  # 前缀和累加器
        while x:  # x 减到 0 时结束
            s += self.c[x]  # 累加当前区间的和
            x -= x & -x  # 拆到前一段区间
        return s  # 返回前缀和


class Solution:  # LeetCode 约定的题解类
    def countOfPeaks(self, nums: List[int], queries: List[List[int]]) -> List[int]:  # nums 是原数组；queries 中 [1,l,r] 表示查询、[2,i,val] 表示修改
        def update(i: int, val: int):  # 内部函数：把下标 i 的「是否为峰」加上 val
            if i <= 0 or i >= n - 1:  # 首尾元素缺少一侧邻居，不可能是峰
                return  # 直接返回，不做任何更新
            if nums[i - 1] < nums[i] and nums[i] > nums[i + 1]:  # 严格大于左右邻居才是峰
                tree.update(i, val)  # 是峰就在树状数组上加 val（val 为 -1 时表示撤销）

        n = len(nums)  # 数组长度
        tree = BinaryIndexedTree(n - 1)  # 峰只可能出现在 1..n-2，上界取 n-1 即可
        for i in range(1, n - 1):  # 初始化：统计原数组中所有峰
            update(i, 1)  # 每个峰在树状数组上记 1
        ans = []  # 按顺序收集每次查询的答案
        for q in queries:  # 依次处理每条操作
            if q[0] == 1:  # 类型 1：查询子数组内的峰个数
                l, r = q[1] + 1, q[2] - 1  # 子数组内的峰只可能出现在这两个下标之间
                ans.append(0 if l > r else tree.query(r) - tree.query(l - 1))  # 长度不足 3 时没有峰，否则用前缀和相减求区间峰数
            else:  # 类型 2：单点修改
                idx, val = q[1:]  # 拆出要修改的下标与新的值
                for i in range(idx - 1, idx + 2):  # 只有 idx-1、idx、idx+1 三处的峰状态可能改变
                    update(i, -1)  # 先撤销这三处在旧值下的贡献
                nums[idx] = val  # 真正修改数组
                for i in range(idx - 1, idx + 2):  # 再按新值重新计算这三处
                    update(i, 1)  # 新状态下是峰就重新登记
        return ans  # 按顺序返回所有查询结果
