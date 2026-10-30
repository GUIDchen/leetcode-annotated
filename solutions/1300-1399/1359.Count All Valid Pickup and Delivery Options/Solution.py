# 题目：1359. 有效的快递序列数目（Count All Valid Pickup and Delivery Options）
# 思路：递推。已排好 i-1 份订单时，第 i 份订单的取件与送件有 i*(2i-1) 种插入方式，故 f(i) = f(i-1) * i * (2i-1)。
# 时间复杂度：O(n)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def countOrders(self, n: int) -> int:  # 求 n 份订单的合法「取件-送件」序列总数
        mod = 10**9 + 7  # 取模常量，满足题目要求
        f = 1  # 递推值：n = 1 时只有 1 种方案（Python 整数不会溢出）
        for i in range(2, n + 1):  # 从 1 份订单逐步扩展到 i 份订单
            f = (f * i * (2 * i - 1)) % mod  # 第 i 份订单可插入 i*(2i-1) 个位置，乘完取模
        return f  # 返回方案数
