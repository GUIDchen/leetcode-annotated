# 题目：762. 二进制表示中质数个计算置位（Prime Number of Set Bits in Binary Representation）
# 思路：把 20 以内可能的置位数质数放进集合，枚举区间内每个数并用 bit_count() 统计 1 的个数再判断。
# 时间复杂度：O(n log C)，n 为区间长度；空间复杂度：O(1)，质数集合大小固定。
class Solution:  # LeetCode 约定的题解类
    def countPrimeSetBits(self, left: int, right: int) -> int:  # 统计 [left, right] 内二进制 1 的个数为质数的整数个数
        primes = {2, 3, 5, 7, 11, 13, 17, 19}  # 预存可能的置位数质数（20 位以内 1 的个数最多为 20）
        return sum(i.bit_count() in primes for i in range(left, right + 1))  # 对每个数求 1 的个数，命中质数集合则计 1，求和返回
