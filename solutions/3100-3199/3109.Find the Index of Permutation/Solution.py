# 题目：3109. 查找排列的下标（Find the Index of Permutation）🔒
# 思路：康托展开求字典序排名，树状数组统计「比当前数字小且尚未使用」的个数，再乘以剩余位的阶乘逐位累加。
# 时间复杂度：O(n log n)，树状数组每次操作 O(log n)；空间复杂度：O(n)，阶乘表与树状数组各占 O(n)。
class BinaryIndexedTree:  # 树状数组，维护 1..n 中哪些数值已经被使用
    __slots__ = "n", "c"  # 限定实例属性，n 是上界、c 是桶数组，避免额外字典开销

    def __init__(self, n: int):  # 构造函数，n 是数值范围上界
        self.n = n  # 记录上界，供 update 的循环条件使用
        self.c = [0] * (n + 1)  # 开 n+1 个桶，树状数组下标从 1 开始

    def update(self, x: int, delta: int) -> None:  # 把位置 x 的值增加 delta
        while x <= self.n:  # 沿父链向上跳，直到越过上界
            self.c[x] += delta  # 当前节点累加增量
            x += x & -x  # 跳到下一个覆盖位置 x 的节点

    def query(self, x: int) -> int:  # 求 1..x 的前缀和
        s = 0  # 前缀和累加器
        while x:  # 只要 x 还大于 0 就继续逐段累加
            s += self.c[x]  # 加上当前段所管区间的和
            x -= x & -x  # 剥掉最低位的 1，继续向下
        return s  # 返回 1..x 的前缀和


class Solution:  # LeetCode 约定的题解类
    def getPermutationIndex(self, perm: List[int]) -> int:  # perm 是待求字典序排名的排列
        mod = 10**9 + 7  # 结果需要对 1e9+7 取模
        ans, n = 0, len(perm)  # ans 累计排名，n 是排列长度
        tree = BinaryIndexedTree(n + 1)  # 数值范围是 1..n，树状数组开到 n+1
        f = [1] * n  # 阶乘表，初始全为 1（即 0! = 1）
        for i in range(1, n):  # 递推求出 1! 到 (n-1)!
            f[i] = f[i - 1] * i % mod  # i! = (i-1)! × i，边乘边取模防止溢出
        for i, x in enumerate(perm):  # 从高位到低位逐位计算贡献
            cnt = x - 1 - tree.query(x)  # 比 x 小且还没被使用过的数字个数
            ans += cnt * f[n - i - 1] % mod  # 本位贡献 = 可选个数 × 剩余位数的全排列数
            tree.update(x, 1)  # 把 x 标记为已使用
        return ans % mod  # 返回取模后的字典序排名
