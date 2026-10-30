# 题目：172. 阶乘后的零（Factorial Trailing Zeroes）
# 思路：末尾零来自因子 10 = 2 × 5，2 远比 5 多，故只统计 1..n 中因子 5 的总数：n//5 + n//25 + n//125 + …。
# 时间复杂度：O(log₅n)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def trailingZeroes(self, n: int) -> int:  # 计算 n! 末尾连续零的个数
        ans = 0  # 记录因子 5 的总个数
        while n:  # 不断除以 5，直到 n 变成 0
            n //= 5  # 整数除法得到这一层的因子 5 个数
            ans += n  # 累加到答案
        return ans  # 返回因子 5 的总数，即末尾零的个数
