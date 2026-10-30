# 3405. 统计恰好有 K 个相等相邻元素的数组数目 / Count the Number of Arrays with K Matching Adjacent Elements
# 核心思路：n 个数共有 n - 1 个相邻位置，选出 k 个相等位置有 C(n-1, k) 种，首元素 m 种，其余 n - 1 - k 个位置只需与前一个不同、各有 m - 1 种，答案为 C(n-1,k) * m * (m-1)^(n-1-k)
# 复杂度：时间 O(MX + log MOD)（预处理阶乘与逆元），空间 O(MX)
mx = 10**5 + 10  # 阶乘预处理的上界
mod = 10**9 + 7  # 取模常数
f = [1] + [0] * mx  # f[i] 表示 i 的阶乘
g = [1] + [0] * mx  # g[i] 表示 f[i] 的逆元

for i in range(1, mx):  # 递推预处理阶乘与逆元
    f[i] = f[i - 1] * i % mod  # i 的阶乘
    g[i] = pow(f[i], mod - 2, mod)  # 费马小定理求逆元


def comb(m: int, n: int) -> int:  # 组合数 C(m, n) = m! / (n! * (m-n)!)
    return f[m] * g[n] * g[m - n] % mod  # 用阶乘与逆元计算组合数


class Solution:  # 定义题目解答类
    def countGoodArrays(self, n: int, m: int, k: int) -> int:  # 方法入口：长度为 n、元素取值 [1, m] 且恰好 k 个相等相邻元素的数组个数
        return comb(n - 1, k) * m * pow(m - 1, n - k - 1, mod) % mod  # 选 k 个相等位置 C(n-1, k)，首元素 m 种，其余 n - 1 - k 个位置各 m - 1 种
