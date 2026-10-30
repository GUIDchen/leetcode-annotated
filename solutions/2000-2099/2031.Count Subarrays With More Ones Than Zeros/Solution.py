# 题目：2031. 1 比 0 多的子数组个数（Count Subarrays With More Ones Than Zeros）
# 思路：把 1 记作 +1、0 记作 -1 求前缀和 s，「子数组和大于 0」等价于 s[j] > s[i]；用树状数组按前缀和值域动态维护历史前缀的出现次数，逐位累加比当前 s 小的历史前缀个数。
# 时间复杂度：O(n log n)，每个元素一次查询加一次更新；空间复杂度：O(n)，树状数组长度约 2n+1（加偏移量避免负下标）。
class BinaryIndexedTree:  # 树状数组（Binary Indexed Tree），维护每个前缀和取值出现的次数
    __slots__ = ["n", "c"]  # 用 __slots__ 限定属性，省内存、防手误新增字段

    def __init__(self, n: int):  # 构造函数：n 是值域上界
        self.n = n  # 保存上界，供 update 的循环条件使用
        self.c = [0] * (n + 1)  # 开 n+1 个桶并全部置 0，下标从 1 开始用，方便 lowbit 运算

    def update(self, x: int, v: int):  # 单点更新：把下标 x 处的计数加上 v
        while x <= self.n:  # x 不断加上最低位 1，沿父链向上更新所有覆盖 x 的节点
            self.c[x] += v  # 给覆盖当前位置的节点累加增量
            x += x & -x  # 跳到下一个父节点

    def query(self, x: int) -> int:  # 前缀查询：返回下标 1..x 范围内所有计数之和
        s = 0  # 累加答案
        while x:  # x 不为 0 时继续；每次减去最低位 1，把 [1, x] 拆成 O(log n) 段
            s += self.c[x]  # 累加该段的和
            x -= x & -x  # 左跳到下一段
        return s  # 返回 [1, x] 的计数总和


class Solution:  # LeetCode 约定的题解类
    def subarraysWithMoreZerosThanOnes(self, nums: List[int]) -> int:  # nums 只含 0/1，返回「1 的个数多于 0 的个数」的子数组个数（对 1e9+7 取模）
        n = len(nums)  # 数组长度
        base = n + 1  # 偏移量：前缀和可能为负，整体加 base 映射成正下标
        tree = BinaryIndexedTree(n + base)  # 树状数组要覆盖 [-n, n] 全部前缀和取值（偏移后为 1..2n+1）
        tree.update(base, 1)  # 空前缀和 s = 0 先计入，作为从下标 0 开始的子数组的左端点
        mod = 10**9 + 7  # 答案需要取模的质数
        ans = s = 0  # ans 记录子数组个数，s 是当前前缀和
        for x in nums:  # 从左到右遍历数组
            s += x or -1  # x 为 1 时加 1，为 0 时加 -1（`x or -1` 的简写技巧）
            ans += tree.query(s - 1 + base)  # 累加以「更小的历史前缀」为起点的子数组个数
            ans %= mod  # 每步取模防止溢出
            tree.update(s + base, 1)  # 把当前前缀和计入树状数组，供后面的位置当左端点
        return ans  # 返回满足条件的子数组总数
