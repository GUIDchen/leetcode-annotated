# 3896. 将数组转换为交替质数数组的最少操作次数 / Minimum Operations to Transform Array into Alternating Prime
# 核心思路：筛出 2e5 以内的质数；偶数下标用二分提升到最近的质数，奇数下标若已是质数则加 1（2 需加 2）使其变成合数。
# 复杂度：时间 O(MX log log MX + n log MX)，空间 O(MX)，其中 MX = 2e5。
MX = 200000  # 数值上界 2e5，与题目元素范围一致
is_prime = [True] * (MX + 1)  # 先假定 0..MX 全为质数
is_prime[0] = is_prime[1] = False  # 0 与 1 不是质数

for i in range(2, int(MX**0.5) + 1):  # 埃氏筛：只需用不超过 sqrt(MX) 的数去筛
    if is_prime[i]:  # i 仍是质数时才用它筛掉倍数
        for j in range(i * i, MX + 1, i):  # 从 i*i 起，步长 i 标记所有倍数
            is_prime[j] = False  # 倍数必为合数

primes = [i for i in range(2, MX + 1) if is_prime[i]]  # 升序收集全部质数，供二分查找使用


class Solution:  # 题解类
    def minOperations(self, nums: list[int]) -> int:  # nums 为待变换数组，返回最少操作次数
        ans = 0  # 累计所需的最少操作次数
        for i, x in enumerate(nums):  # 按下标逐位处理
            if i % 2 == 0:  # 偶数下标最终必须是质数（只能单调增大）
                j = bisect_left(primes, x)  # 二分找到第一个不小于 x 的质数的下标
                ans += primes[j] - x  # 差值即本位所需操作次数
            else:  # 奇数下标最终必须是合数
                if is_prime[x]:  # 原本是质数才需要改动
                    ans += 2 if x == 2 else 1  # 质数加 1 即为合数，x = 2 时须加 2
        return ans  # 返回最少操作次数
