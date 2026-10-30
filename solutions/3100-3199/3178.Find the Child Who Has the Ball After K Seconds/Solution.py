# 题目：3178. 找出 K 秒后拿着球的孩子（Find the Child Who Has the Ball After K Seconds）
# 思路：传球方向每 n-1 秒翻转一次，用 divmod 把 k 拆成「完整周期数」和「周期内偏移量」，再按周期奇偶决定方向。
# 时间复杂度：O(1)，只做常数次算术运算；空间复杂度：O(1)，只用了几个整型变量。
class Solution:  # LeetCode 约定的题解类
    def numberOfChild(self, n: int, k: int) -> int:  # n：孩子数量；k：经过的秒数
        k, mod = divmod(k, n - 1)  # 一个往返周期是 n-1 秒，k 变为完整周期数，mod 为周期内偏移量
        return n - mod - 1 if k & 1 else mod  # 奇数周期表示在回程，下标为 n-mod-1；偶数周期在去程，下标为 mod
