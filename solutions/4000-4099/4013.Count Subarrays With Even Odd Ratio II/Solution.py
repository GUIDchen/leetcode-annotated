# 题目：4013. 按奇偶比统计子数组 II（Count Subarrays With Even Odd Ratio II）
# 思路：把奇数记 +a、偶数记 -b 构造前缀和，则 x / y <= a / b 等价于 s[r] - s[l] >= 0；离散化前缀和后用树状数组统计「前面有多少个前缀和不大于当前值」，累加即得答案。
# 时间复杂度：O(n log n)，排序与树状数组；空间复杂度：O(n)，前缀和、离散化数组与树状数组。
class BinaryIndexedTree:  # 树状数组（Binary Indexed Tree），用于按前缀和计数
    __slots__ = "n", "c"  # 用 __slots__ 固定属性，减少每个实例的内存开销

    def __init__(self, n: int):  # 构造函数：n 是下标上界
        self.n = n  # 记录下标上界
        self.c = [0] * (n + 1)  # 内部数组取 n + 1 长度，便于 1 基编号

    def update(self, x: int, delta: int) -> None:  # 单点更新：把下标 x 处的计数增加 delta
        while x <= self.n:  # 沿 lowbit 向上爬
            self.c[x] += delta  # 累加到覆盖该位置的节点
            x += x & -x  # x 加上自身最低位的 1

    def query(self, x: int) -> int:  # 前缀查询：返回下标 1..x 的计数总和
        s = 0  # s 累计查询结果
        while x:  # 沿 lowbit 向下跳
            s += self.c[x]  # 累加当前节点
            x -= x & -x  # x 减去自身最低位的 1
        return s  # 返回前缀计数


class Solution:  # LeetCode 约定的题解类
    def countRatioSubarrays(self, nums: list[int], a: int, b: int) -> int:  # nums：待统计的数组；a、b：比值上界 a / b；返回满足条件的子数组个数
        n = len(nums)  # n 为数组长度
        s = [0] * (n + 1)  # 前缀和：奇数记 +a，偶数记 -b
        for i, x in enumerate(nums):  # 逐项递推前缀和
            s[i + 1] = s[i] + (a if x % 2 else -b)  # 奇数记 +a、偶数记 -b，使「偶数个数比上奇数个数不超过 a/b」等价于区间和不小于 0

        st = sorted(set(s))  # 离散化：排序去重，把前缀和映射成紧凑下标
        bit = BinaryIndexedTree(len(st) + 1)  # 树状数组规模取离散值个数 + 1（内部 1 基下标）
        ans = 0  # ans 记录满足条件的子数组个数
        for v in s:  # 顺序遍历每个前缀和
            x = bisect_left(st, v) + 1  # 前缀和对应的 1 基离散下标
            ans += bit.query(x)  # 前面有多少个前缀和 <= 当前值，就有多少个满足条件的子数组
            bit.update(x, 1)  # 把当前前缀和也加入树状数组
        return ans  # 返回满足条件的子数组总数
