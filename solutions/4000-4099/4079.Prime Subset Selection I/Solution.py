# 4079. 选择质数子集 I（Prime Subset Selection I）
# 核心思路：先用埃氏筛预处理 1e6 以内的质数表，再按升序贪心取质数：只要当前质数不超过 n 且不超过剩余额度 s 就选入，这样个数最多。
# 复杂度：预处理 O(M log log M)（M = 1e6），单次查询 O(答案长度)，空间 O(M)。
mx = 10**6  # 筛法上界 1e6
primes = []  # 存放所有不超过上界的质数（升序）
is_prime = [True] * (mx + 1)  # 布尔筛表，初始都标记为质数
is_prime[0] = is_prime[1] = False  # 0 和 1 不是质数

for i in range(2, mx + 1):  # 从小到大扫描每个数
    if is_prime[i]:  # i 仍被标记为质数
        primes.append(i)  # 把 i 收进质数表
        if i * i <= mx:  # 判断 i * i 是否超过上界
            for j in range(i * i, mx + 1, i):  # 把 i 从 i * i 开始的所有倍数标记为合数
                is_prime[j] = False  # 倍数置为合数


class Solution:  # 题解类
    def maxPrimes(self, n: int, s: int) -> list[int]:  # 在质数不超过 n、所选质数之和不超过 s 的前提下，选出数量尽可能多的质数
        ans = []  # 选出的质数列表
        for p in primes:  # 按升序尝试每个质数
            if p > n or p > s:  # 当前质数超过上限 n，或剩余额度 s 不足以再选它
                break  # 后面的质数只会更大，同样不行，直接结束
            ans.append(p)  # 贪心地选入当前最小的可用质数
            s -= p  # 扣减已占用的额度
        return ans  # 返回选出的质数列表（升序且个数最多）
