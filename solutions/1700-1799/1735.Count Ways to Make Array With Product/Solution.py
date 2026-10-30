# 题目：1735. 生成乘积数组的方案数（Count Ways to Make Array With Product）
# 思路：预处理阶乘、逆元与每个数的质因子指数；对每个 k 分解质因数，指数 c 用隔板法得到 C(c+n-1, n-1)，各质因子方案数相乘即为答案。
# 时间复杂度：预处理 O(N·√N)，单次查询 O(k 的质因子个数)；空间复杂度：O(N) 的阶乘、逆元与质因子表。
N = 10020  # 预处理上界，覆盖 n、k 的最大取值
MOD = 10**9 + 7  # 取模的模数
f = [1] * N  # f[i] 保存 i! 对 MOD 取模的结果
g = [1] * N  # g[i] 保存 i! 的模逆元
p = defaultdict(list)  # p[i] 保存 i 的所有质因子指数，例如 12 -> [2, 1]（来自 2^2 * 3^1）
for i in range(1, N):  # 从 1 到 N-1 逐个打表
    f[i] = f[i - 1] * i % MOD  # 用上一个阶乘递推出 i!
    g[i] = pow(f[i], MOD - 2, MOD)  # 费马小定理求逆元
    x = i  # 临时变量用于质因数分解，保留 i 本身供下标使用
    j = 2  # 试除因子从 2 开始
    while j <= x // j:  # 只枚举到 sqrt(x)，写 j <= x // j 可避免溢出
        if x % j == 0:  # j 是 x 的一个质因子
            cnt = 0  # 记录该质因子的指数
            while x % j == 0:  # 反复除尽这个质因子
                cnt += 1  # 指数加一
                x //= j  # 除去一个 j
            p[i].append(cnt)  # 记下该质因子的指数
        j += 1  # 试下一个因子
    if x > 1:  # 剩余部分大于 1，说明它本身是质数
        p[i].append(1)  # 这个质因子的指数为 1


def comb(n, k):  # 计算组合数 C(n, k)
    return f[n] * g[k] * g[n - k] % MOD  # 等价于 n! / (k! * (n-k)!)，最后统一取模


class Solution:  # LeetCode 约定的题解类
    def waysToFillArray(self, queries: List[List[int]]) -> List[int]:  # queries[i] = [n, k]
        ans = []  # 按查询顺序保存答案
        for n, k in queries:  # 逐个查询处理
            t = 1  # 当前查询的方案数
            for x in p[k]:  # 枚举 k 的每个质因子的指数 x
                t = t * comb(x + n - 1, n - 1) % MOD  # 隔板法：x 个相同质因子分给 n 个位置共 C(x+n-1, n-1) 种
            ans.append(t)  # 记录该查询的答案
        return ans  # 返回全部答案
