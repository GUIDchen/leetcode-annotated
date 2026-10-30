# 题目：2539. 好子序列的个数（Count the Number of Good Subsequences）
# 思路：统计各字符频次后，枚举子序列中各字符出现的统一次数 i；可用字符贡献 C(v, i)+1 种选择，
# 连乘后减 1（去掉空串）累加。时间 O(N + 26·maxcnt)，空间 O(N)，N 为预处理上限。
N = 10001  # 预处理规模：长度上限 10000 再加 1
MOD = 10**9 + 7  # 取模常量
f = [1] * N  # f[i] 将存放 i! mod MOD
g = [1] * N  # g[i] 将存放 i! 的逆元 mod MOD
for i in range(1, N):  # 从 1 递推到 N-1，做好阶乘预处理
    f[i] = f[i - 1] * i % MOD  # 阶乘递推：f[i] = f[i-1] * i
    g[i] = pow(f[i], MOD - 2, MOD)  # 费马小定理求逆元：a^(MOD-2) mod MOD


def comb(n, k):  # 组合数 C(n, k) mod MOD
    return f[n] * g[k] * g[n - k] % MOD  # 分子乘上两个逆阶乘，等价于模意义下的整体除法


class Solution:  # LeetCode 约定的题解类
    def countGoodSubsequences(self, s: str) -> int:  # s 为输入字符串，返回好子序列的个数
        cnt = Counter(s)  # 统计每个字符的出现次数
        ans = 0  # 答案累加器
        for i in range(1, max(cnt.values()) + 1):  # 枚举子序列中各字符出现的统一次数 i，上界是最大频率
            x = 1  # 本轮方案数，从 1 开始连乘
            for v in cnt.values():  # 遍历各字符的出现次数
                if v >= i:  # 该字符数量够选出 i 个
                    x = x * (comb(v, i) + 1) % MOD  # C(v, i) 种选法再加 1 种「不选」，乘进方案数
            ans = (ans + x - 1) % MOD  # 减去所有字符都不选的空串，累加到答案并取模
        return ans  # 返回不同好子序列的个数
