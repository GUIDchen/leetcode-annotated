# 4051. 统计遥远子数组的数目（Count Subarrays with Distant Sums）
# 核心思路：先求前缀和，再用树状数组按值域统计与 goal 距离不足 k 的右端点对，从全部子数组中扣除
# 复杂度：时间 O(n log n)，空间 O(n)
class BinaryIndexedTree:  # 树状数组（Fenwick 树）封装
    __slots__ = "n", "c"  # 用 __slots__ 限制实例属性，节省内存

    def __init__(self, n: int):  # 构造函数，n 为可用下标的最大值
        self.n = n  # 记录长度上限
        self.c = [0] * (n + 1)  # 开辟 n + 1 个桶并置 0，采用 1 基下标

    def update(self, x: int, delta: int) -> None:  # 在下标 x 处加上 delta
        while x <= self.n:  # 沿 lowbit 一路向上更新到树根
            self.c[x] += delta  # 当前节点累加增量
            x += x & -x  # 跳到下一个覆盖该位置的节点

    def query(self, x: int) -> int:  # 查询区间 [1, x] 的前缀和
        s = 0  # 累加器从 0 开始
        while x:  # 下标归零后停止
            s += self.c[x]  # 累加当前块的值
            x -= x & -x  # 跳到前一个互不重叠的块
        return s  # 返回前缀和


class Solution:  # 题解主类
    def distantSubarrays(self, nums: list[int], goal: int, k: int) -> int:  # 统计满足条件的子数组个数
        s = list(accumulate(nums, initial=0))  # 前缀和数组，含空前缀 0
        st = sorted(s)  # 排序得到有序值表，便于二分出下标
        n = len(nums)  # 数组长度
        ans = (1 + n) * n // 2  # 先按全部子数组计数，之后逐个扣除不合法的
        bit = BinaryIndexedTree(len(st) + 1)  # 树状数组按离散化后的值域大小开空间
        for v in s:  # 以当前前缀和作为右端点 v，逐个处理
            a = v - goal - k + 1  # 需要扣除的窗口左端 a：距离 goal 不足 k 的前缀和从这里开始
            b = v - goal + k - 1  # 需要扣除的窗口右端 b：到这个值为止都算距离不足

            l = bisect_left(st, a) + 1  # 窗口左端在有序表中的 1 基下标
            r = bisect_left(st, b + 1)  # 第一个大于 b 的位置恰是闭区间右端的 1 基下标
            if l <= r:  # 窗口非空才有需要扣除的对象
                ans -= bit.query(r) - bit.query(l - 1)  # 减去已插入树状数组中落在窗口内的前缀和个数
            bit.update(bisect_left(st, v) + 1, 1)  # 把当前前缀和插入树状数组，供后续右端点查询
        return ans  # 返回满足条件的子数组数目
