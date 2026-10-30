# 3610. 目标和所需的最小质数个数 / Minimum Number of Primes to Sum to Target
# 核心思路：模块级先试除已有质数预处理出前 1000 个质数，再把其中最小的 m 个质数当作物品做完全背包，求凑出目标和 n 所需的最少质数个数。
# 复杂度：时间 O(M·π(√M) + m·n)，空间 O(n)；M = 1000。
primes = []  # 全局质数表，模块导入时就开始构建
x = 2  # 从 2 开始逐个试除
M = 1000  # 需要的前 M 个质数
while len(primes) < M:  # 一直生成到够 M 个质数为止
    is_prime = True  # 先假设当前数 x 是质数
    for p in primes:  # 用已有质数试除
        if p * p > x:  # 试除因子已超过平方根，说明 x 是质数
            break  # 跳出试除循环
        if x % p == 0:  # 能被整除说明不是质数
            is_prime = False  # 标记为合数
            break  # 无需再试除，直接跳出
    if is_prime:  # 确认为质数就收进质数表
        primes.append(x)  # 把 x 加入质数表
    x += 1  # 继续检查下一个数


class Solution:  # 题解类
    def minNumberOfPrimes(self, n: int, m: int) -> int:  # 主函数：用最小的 m 个质数凑出目标和 n 的最少个数
        min = lambda x, y: x if x < y else y  # 为了加速，用 lambda 覆盖内置 min（只支持两个参数）
        f = [0] + [inf] * n  # f[i] 表示凑出 i 所需的最少质数个数，0 需要 0 个
        for x in primes[:m]:  # 只遍历最小的 m 个质数，可重复使用（完全背包）
            for i in range(x, n + 1):  # 从 x 开始向后推导每个可达的和
                f[i] = min(f[i], f[i - x] + 1)  # 比较“不用这个质数”和“再用一个质数”两种方案
        return f[n] if f[n] < inf else -1  # 不可达时返回 -1，否则返回最少个数
