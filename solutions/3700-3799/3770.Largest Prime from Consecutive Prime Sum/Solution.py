# 3770. 可表示为连续质数和的最大质数 / Largest Prime from Consecutive Prime Sum
# 核心思路：先用埃氏筛求出 5×10^5 以内的全部质数，再把从 2 开始的连续质数累加和中本身为质数的值收集成升序表，最后二分查表。
# 复杂度：时间 O(MX·log log MX + log MX)，空间 O(MX)。
mx = 500000  # 预处理上界
is_prime = [True] * (mx + 1)  # 埃氏筛的质数标记数组
is_prime[0] = is_prime[1] = False  # 0 和 1 不是质数
primes = []  # 质数列表
for i in range(2, mx + 1):  # 从 2 开始筛选
    if is_prime[i]:  # i 是质数
        primes.append(i)  # 记录该质数
        for j in range(i * i, mx + 1, i):  # 从 i*i 开始划掉 i 的所有倍数
            is_prime[j] = False  # 标记为合数
s = [0]  # 结果表以 0 开头，保证 n 很小时也能取到合法值
t = 0  # 连续质数的累加和
for x in primes:  # 依次累加每个质数
    t += x  # 累加当前质数
    if t > mx:  # 累加和超过上界
        break  # 后续只会更大，跳出循环
    if is_prime[t]:  # 累加和本身也是质数
        s.append(t)  # 记录该质数


class Solution:  # 定义解法类
    def largestPrime(self, n: int) -> int:  # 求不超过 n 的最大“可表示为连续质数和”的质数
        i = bisect_right(s, n) - 1  # 二分找到最后一个不超过 n 的下标
        return s[i]  # 返回该位置上的质数
