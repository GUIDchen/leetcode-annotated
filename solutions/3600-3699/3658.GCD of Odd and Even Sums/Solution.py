# 3658. 奇数和与偶数和的最大公约数（GCD of Odd and Even Sums）
# 核心思路：前 n 个奇数之和为 n^2，前 n 个偶数之和为 n(n+1)，二者最大公约数恒为 n，故直接返回 n。
# 复杂度：时间 O(1)，空间 O(1)。
class Solution:  # 定义题解类
    def gcdOfOddEvenSums(self, n: int) -> int:  # 前 n 个奇数之和为 n*n、前 n 个偶数之和为 n*(n+1)，两者的最大公约数恒为 n
        return n  # 直接返回 n
