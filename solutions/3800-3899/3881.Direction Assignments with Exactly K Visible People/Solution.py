# 3881. 恰好看到 K 个人的方向选择 / Direction Assignments with Exactly K Visible People
# 核心思路：预处理阶乘与阶乘逆元求组合数，枚举左侧可见人数 a 与右侧可见人数 b = k - a，两侧朝向各计一种。
# 复杂度：时间 O(N + k)，空间 O(N)。
N = 100001  # 预处理规模上限
MOD = 10**9 + 7  # 取模常量 1e9 + 7
f = [1] * N  # 阶乘表
g = [1] * N  # 阶乘逆元表
for i in range(1, N):  # 递推计算所有阶乘
    f[i] = f[i - 1] * i % MOD  # i! = (i-1)! * i
    g[i] = pow(f[i], MOD - 2, MOD)  # 由费马小定理求 i! 的逆元


def comb(n, k):  # 组合数 C(n, k)
    return f[n] * g[k] * g[n - k] % MOD  # 阶乘与两个逆元连乘并取模


class Solution:  # 定义题解类
    def countVisiblePeople(self, n: int, pos: int, k: int) -> int:  # 统计恰好看到 k 个人的方向方案数
        l, r = pos, n - pos - 1  # 左侧与右侧可用的人数
        ans = 0  # 方案数累加器
        for a in range(min(k, l) + 1):  # 枚举左侧被看到的人数
            b = k - a  # 右侧被看到的人数 b
            if b <= r:  # 右侧人数可行才计入
                ans += 2 * comb(l, a) * comb(r, b)  # 左右两种朝向各一种，累加组合数乘积
                ans %= MOD  # 及时取模防止数值过大
        return ans  # 返回方案总数
