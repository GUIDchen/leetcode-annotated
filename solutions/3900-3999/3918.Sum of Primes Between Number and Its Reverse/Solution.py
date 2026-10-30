# 3918. Sum of Primes Between Number and Its Reverse | 数与其逆序数之间的质数和（中等）
# 核心思路：数值上界只有 1000，先在模块级用埃拉托斯特尼筛预处理素数表；单次查询时把 n 的数字逆序得到 r，取 min(n, r) 与 max(n, r) 作为闭区间两端，枚举区间并把其中的素数累加。
# 复杂度：预处理 O(limit log log limit) 时间、O(limit) 空间；每次查询 O(log n + limit) 时间、O(1) 额外空间。
limit = 1000  # 数值上界
is_prime = [True] * (limit + 1)  # 素数标记数组，下标范围 0..limit，先全部视为素数
is_prime[0] = is_prime[1] = False  # 0 和 1 不是素数
for i in range(2, int(limit**0.5) + 1):  # 外层只需枚举到 sqrt(limit)
    if is_prime[i]:  # i 仍是素数时才用它去筛倍数
        for j in range(i * i, limit + 1, i):  # 从 i*i 开始把所有 i 的倍数划掉（更小的倍数已被更小的素数筛过）
            is_prime[j] = False  # 标记为合数


class Solution:  # 定义题解类
    def sumOfPrimesInRange(self, n: int) -> int:  # 返回 n 与其逆序数之间（含两端）的所有素数之和
        r = int(str(n)[::-1])  # 把 n 转成字符串反转再转回整数，即逆序数
        low = min(n, r)  # 区间左端取 n 与 r 的较小者
        high = max(n, r)  # 区间右端取 n 与 r 的较大者
        return sum(x for x in range(low, high + 1) if is_prime[x])  # 枚举闭区间，把查表判定为素数的元素求和后返回
