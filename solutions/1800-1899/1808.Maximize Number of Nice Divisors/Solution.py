# 题目：1808. 好因子的最大数目（Maximize Number of Nice Divisors）
# 思路：把质因子尽量拆成 3 相乘最优；余 1 时改成 2+2（少一个 3 乘 4），余 2 时再乘一个 2，用带模快速幂。
# 时间复杂度：O(log n)，pow 内部对指数做二进制拆分；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def maxNiceDivisors(self, primeFactors: int) -> int:  # primeFactors：可用的质因子个数（把这些质因子相乘凑成一个数 n）
        mod = 10**9 + 7  # 模数 1e9 + 7，所有中间结果都要取模
        if primeFactors < 4:  # 质因子个数小于 4 时，不再拆分最划算
            return primeFactors  # 1、2、3 的最优值就是它自己
        if primeFactors % 3 == 0:  # 能被 3 整除：全部拆成 3
            return pow(3, primeFactors // 3, mod) % mod  # pow(a, b, mod) 是 Python 内置的带模快速幂
        if primeFactors % 3 == 1:  # 除以 3 余 1：把最后的 3+1 换成 2+2 更优
            return 4 * pow(3, primeFactors // 3 - 1, mod) % mod  # 少用一个 3（指数减 1），再多乘一个 4
        return 2 * pow(3, primeFactors // 3, mod) % mod  # 除以 3 余 2：直接再多乘一个因子 2
