# 题目：1952. 三除数（Three Divisors）
# 思路：2..n-1 中恰好有 1 个数能整除 n 时，加上 1 和 n 本身，除数总数正好是 3。
# 时间复杂度：O(n)，一次线性枚举；空间复杂度：O(1)，生成器不额外占用空间。
class Solution:  # LeetCode 约定的题解类
    def isThree(self, n: int) -> bool:  # n：待判断的正整数
        return sum(n % i == 0 for i in range(2, n)) == 1  # 统计真除数个数是否恰为 1
