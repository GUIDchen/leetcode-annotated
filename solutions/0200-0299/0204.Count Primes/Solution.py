# 题目：204. 计数质数（Count Primes）
# 思路：埃拉托斯特尼筛法。从 2 扫到 n-1，遇到仍标记为质数的 i 就计数，并从 2i 起把 i 的倍数全部标记为合数。
# 时间复杂度：O(n log log n)，调和级数量级；空间复杂度：O(n)，标记数组。
class Solution:  # LeetCode 约定的题解类
    def countPrimes(self, n: int) -> int:  # 统计严格小于 n 的质数个数
        primes = [True] * n  # 筛法数组：下标 i 为 True 表示 i 还没被筛掉，先假定都是质数
        ans = 0  # 质数计数器
        for i in range(2, n):  # 0、1 不是质数，从 2 扫到 n-1
            if primes[i]:  # 仍为 True 说明没有被更小的质数标记过，i 是质数
                ans += 1  # 计入答案
                for j in range(i + i, n, i):  # 步长 i 遍历 i 的所有倍数；从 2i 开始是因为 i 本身已经算过质数了
                    primes[j] = False  # 把该倍数标记为合数
        return ans  # 返回小于 n 的质数个数
