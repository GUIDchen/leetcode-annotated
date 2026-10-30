# 题目：1227. 飞机座位分配概率（Airplane Seat Assignment Probability）
# 思路：n = 1 时第一位乘客就是第 n 位乘客，必坐对；n ≥ 2 时随机的第一位乘客让最后两个座位等概率，答案是 1/2。
# 时间复杂度：O(1)，只做一次比较；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def nthPersonGetsNthSeat(self, n: int) -> float:  # n：乘客（座位）总数，返回第 n 位乘客坐到自己座位的概率
        return 1 if n == 1 else 0.5  # n 为 1 时概率为 1，否则恒为 0.5
