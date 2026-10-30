# 题目：878. 第 N 个神奇数字（Nth Magical Number）
# 核心思路：二分答案，用容斥 x // a + x // b - x // lcm(a, b) 统计不超过 x 的神奇数个数，bisect_left 找第一个个数达到 n 的 x。
# 时间复杂度：O(log((a + b) * n))，二分次数为对数级；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def nthMagicalNumber(self, n: int, a: int, b: int) -> int:  # n：要求的第几个；a、b：两个正整数，神奇数是能被 a 或 b 整除的数
        mod = 10**9 + 7  # 题目要求的取模常量
        c = lcm(a, b)  # 最小公倍数，用于容斥去重
        r = (a + b) * n  # 二分上界：第 n 个神奇数一定小于它
        return bisect_left(range(r), x=n, key=lambda x: x // a + x // b - x // c) % mod  # 在 0..r-1 上做二分：key 是「不超过 x 的神奇数个数」，找到第一个个数 >= n 的位置（range 的下标值恰好等于数值本身），再取模返回
