# 题目：1175. 质数排列（Prime Arrangements）
# 思路：1..n 中质数有 cnt 个，质数只能与质数互换位置，所以答案是 cnt! × (n-cnt)!；用埃氏筛统计 cnt，用 factorial 求阶乘后取模。
# 时间复杂度：O(n log log n)，埃氏筛加两次阶乘；空间复杂度：O(n)，筛法使用的布尔数组。
class Solution:  # 题解类
    def numPrimeArrangements(self, n: int) -> int:  # 求质数排布数
        def count(n):  # 内部函数：用埃氏筛统计 1..n 中质数的个数
            cnt = 0  # 质数计数器
            primes = [True] * (n + 1)  # 布尔数组标记每个数是否为质数，先全部当作是
            for i in range(2, n + 1):  # 从 2 开始向下筛
                if primes[i]:  # i 仍然是质数
                    cnt += 1  # 质数个数加一
                    for j in range(i + i, n + 1, i):  # 把 i 的所有倍数标记为非质数
                        primes[j] = False  # 标记为非质数
            return cnt  # 返回质数个数

        cnt = count(n)  # 质数个数 cnt
        ans = factorial(cnt) * factorial(n - cnt)  # 质数内部全排列 × 合数内部全排列
        return ans % (10**9 + 7)  # 对 10^9+7 取模后返回
