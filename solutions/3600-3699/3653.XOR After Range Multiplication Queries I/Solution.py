# 3653. 区间乘法查询后的异或 I（XOR After Range Multiplication Queries I）
# 核心思路：直接按题意模拟每个查询，从 l 开始以 k 为步长把区间内的元素乘上 v 并取模，最后把整个数组异或起来。
# 复杂度：时间 O(Σ((r-l)/k + 1))，空间 O(1)。
class Solution:  # 定义题解类
    def xorAfterQueries(self, nums: List[int], queries: List[List[int]]) -> int:  # 依次执行所有查询，返回最终数组所有元素的异或值
        mod = 10**9 + 7  # 取模常量 10^9 + 7
        for l, r, k, v in queries:  # 遍历每个查询，拆出左端点 l、右端点 r、步长 k、乘数 v
            for idx in range(l, r + 1, k):  # 从 l 开始按步长 k 枚举区间内的下标（含右端点 r）
                nums[idx] = nums[idx] * v % mod  # 该位置乘上 v 并取模
        return reduce(xor, nums)  # 用 reduce 把 xor 作用到整个数组上，一步求出异或和
