# 4002. 统计有效序列数目 / Count Valid Sequences（中等）
# 核心思路：长度为 k、和为 n 的正整数序列用隔板法共 C(n-1, k-1) 个；乘积为奇数等价于每个数都是奇数，这类序列有 C((n+k)/2 - 1, k-1) 个（仅当 n+k 为偶数时存在），容斥相减即得乘积为偶数的方案数。
# 复杂度：预处理 O(MX log MOD) 时间与 O(MX) 空间，单次查询 O(1)。
MX = 5 * 10**5 + 1  # 预处理规模：n 最大 5 * 10^5
MOD = 10**9 + 7  # 取模用的模数
f = [1] * MX  # f[i] 将存放 i! % MOD
g = [1] * MX  # g[i] 将存放 (i!)^(MOD-2) % MOD，即阶乘的模逆元
for i in range(1, MX):  # 从小到大递推阶乘与阶乘逆元
    f[i] = f[i - 1] * i % MOD  # 递推阶乘
    g[i] = pow(f[i], MOD - 2, MOD)  # 用内置 pow 的模幂求阶乘逆元（费马小定理）


def comb(n: int, k: int) -> int:  # 组合数 C(n, k) % MOD
    return f[n] * g[k] * g[n - k] % MOD  # n! / (k! (n-k)!)，用逆元相乘代替除法


class Solution:  # 题解类
    def countValidSequences(self, n: int, k: int) -> int:  # 返回长度为 k、和为 n 且乘积为偶数的序列个数
        ans = comb(n - 1, k - 1)  # 隔板法：忽略奇偶性限制的全部序列数
        if (n + k) % 2 == 0:  # 只有 n+k 为偶数时，才存在「全为奇数」的序列
            ans = (ans - comb((n + k) // 2 - 1, k - 1)) % MOD  # 容斥减去乘积为奇数（全为奇数）的方案，Python 取模结果自动非负
        return ans  # 返回答案
