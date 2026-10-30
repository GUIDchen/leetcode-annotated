# 题目：1716. 计算力扣银行的钱（Calculate Money in Leetcode Bank）
# 思路：第 i 周每天存入 i, i+1, ..., i+6，一周共 7i+21；前 k 个完整周是首项 28、公差 7 的等差数列，剩余 b 天是首项 k+1、公差 1 的等差数列，分别求和。
# 时间复杂度：O(1)；空间复杂度：O(1)。
class Solution:
    def totalMoney(self, n: int) -> int:  # 计算前 n 天一共存了多少钱
        k, b = divmod(n, 7)  # divmod 一次得到完整周数 k 与不足一周的天数 b
        s1 = (28 + 28 + 7 * (k - 1)) * k // 2  # 前 k 周：首项 28、公差 7 的等差数列求和公式
        s2 = (k + 1 + k + 1 + b - 1) * b // 2  # 剩余 b 天：首项 k+1、末项 k+b 的等差数列求和公式
        return s1 + s2  # 两部分相加得到总额
