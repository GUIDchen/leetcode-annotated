# 题目：3233. 统计不是特殊数字的数字数量（Find the Count of Numbers Which Are Not Special）
# 思路：特殊数字恰好是素数的平方。先用埃氏筛预处理到 sqrt(1e9) 的素数表，再数出 [l, r] 中平方根为素数的个数，用区间长度减掉它。
# 时间复杂度：预处理 O(√R log log √R)，单次查询 O(√R)；空间复杂度：O(√R)，用于存放素数表。
m = 31623  # sqrt(1e9) 的上取整，筛表规模上限
primes = [True] * (m + 1)  # primes[i] 表示 i 是否为素数
primes[0] = primes[1] = False  # 0 和 1 都不是素数
for i in range(2, m + 1):  # 埃拉托斯特尼筛：从小到大枚举每个数
    if primes[i]:  # 只处理素数
        for j in range(i + i, m + 1, i):  # 从 2i 开始，把 i 的所有倍数标记为合数
            primes[j] = False  # 标记合数


class Solution:  # LeetCode 约定的题解类
    def nonSpecialCount(self, l: int, r: int) -> int:  # 统计区间 [l, r] 中不是“特殊数字”的个数
        lo = ceil(sqrt(l))  # 特殊数字形如 p²，其平方根的下界
        hi = floor(sqrt(r))  # 特殊数字形如 p²，其平方根的上界
        cnt = sum(primes[i] for i in range(lo, hi + 1))  # 区间内特殊数字的个数（平方根为素数的那些）
        return r - l + 1 - cnt  # 区间总个数减去特殊数字个数，即答案
