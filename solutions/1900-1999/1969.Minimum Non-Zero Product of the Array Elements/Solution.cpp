// 题目：1969. 数组元素的最小非零乘积（Minimum Non-Zero Product of the Array Elements）
// 思路：数组是 1 到 2^p-1，把除最大值外的元素两两配对、把 1 位从一侧挪到另一侧，可让每对乘积（含一个 2^k-1）最小；最终答案为 (2^p-1) * (2^p-2)^(2^(p-1)-1)，用快速幂取模。
// 时间复杂度：O(p)，快速幂的指数有 p 位；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minNonZeroProduct(int p) {  // p：数组由 1 到 2^p-1 构成
        using ll = long long;  // 中间乘积会超出 int，统一用 64 位整数
        const int mod = 1e9 + 7;  // 题目要求的取模模数
        auto qpow = [](ll a, ll n) {  // 快速幂：计算 a^n % mod
            ll ans = 1;  // 累积结果，乘法单位元
            for (; n; n >>= 1) {  // 逐个二进制位处理指数
                if (n & 1) {  // 当前最低位为 1，说明这一份 a^(2^k) 要乘进结果
                    ans = ans * a % mod;  // 乘上当前底数后立即取模，防止溢出
                }
                a = a * a % mod;  // 底数平方，准备下一次的 a^(2^(k+1))
            }
            return ans;  // 返回 a^n % mod 的结果
        };
        ll a = ((1LL << p) - 1) % mod;  // 数组最大值 2^p-1，先取模
        ll b = qpow(((1LL << p) - 2) % mod, (1L << (p - 1)) - 1);  // (2^p-2) 的 (2^(p-1)-1) 次幂，即配对后其余因子的乘积
        return a * b % mod;  // 两部分相乘再取模即为最小非零乘积
    }
};