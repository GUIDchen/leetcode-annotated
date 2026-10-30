# 题目：1922. 统计好数字的数目（Count Good Numbers）
# 思路：数学 + 快速幂。偶数下标可用 0/2/4/6/8 共 5 种，奇数下标可用 2/3/5/7 共 4 种；答案即 5^ceil(n/2) * 4^floor(n/2) mod 1e9+7，用内置 pow 的三参数形式做快速幂。
# 时间复杂度：O(log n)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def countGoodNumbers(self, n: int) -> int:  # n 是数字串长度，返回长度为 n 的好数字串个数（对 1e9+7 取模）
        mod = 10**9 + 7  # 取模用的大质数
        return pow(5, (n + 1) >> 1, mod) * pow(4, n >> 1, mod) % mod  # 偶数位（共 (n+1)>>1 个）5 种选择、奇数位（共 n>>1 个）4 种选择，分别快速幂后相乘取模
