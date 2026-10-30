// 3405. 统计恰好有 K 个相等相邻元素的数组数目 / Count the Number of Arrays with K Matching Adjacent Elements
// 核心思路：n 个数共有 n - 1 个相邻位置，选出 k 个相等位置有 C(n-1, k) 种，首元素 m 种，其余 n - 1 - k 个位置只需与前一个不同、各有 m - 1 种，答案为 C(n-1,k) * m * (m-1)^(n-1-k)
// 复杂度：时间 O(MX + log MOD)（预处理阶乘与逆元），空间 O(MX)
const int MX = 1e5 + 10;  // 阶乘预处理的上界
const int MOD = 1e9 + 7;  // 取模常数
long long f[MX];  // f[i] 表示 i 的阶乘
long long g[MX];  // g[i] 表示 f[i] 的逆元

long long qpow(long a, int k) {  // 快速幂：求 a^k mod MOD
    long res = 1;  // 累乘结果
    while (k != 0) {  // 指数未归零就继续
        if ((k & 1) == 1) {  // 当前二进制位为 1
            res = res * a % MOD;  // 把 a 乘入结果
        }
        k >>= 1;  // 指数右移一位
        a = a * a % MOD;  // 底数平方
    }
    return res;  // 返回 a^k mod MOD
}

int init = []() {  // 用 lambda 在程序启动时完成阶乘与逆元的预处理
    f[0] = g[0] = 1;  // 0 的阶乘及其逆元都是 1
    for (int i = 1; i < MX; ++i) {  // 递推计算 1 到 MX - 1 的阶乘
        f[i] = f[i - 1] * i % MOD;  // i 的阶乘
        g[i] = qpow(f[i], MOD - 2);  // 费马小定理求逆元
    }
    return 0;  // 返回值只用于触发初始化，内容无意义
}();

long long comb(int m, int n) {  // 组合数 C(m, n) = m! / (n! * (m-n)!)
    return f[m] * g[n] % MOD * g[m - n] % MOD;  // 用阶乘与逆元计算组合数
}

class Solution {  // 定义题目解答类
public:
    int countGoodArrays(int n, int m, int k) {  // 方法入口：长度为 n、元素取值 [1, m] 且恰好 k 个相等相邻元素的数组个数
        return comb(n - 1, k) * m % MOD * qpow(m - 1, n - k - 1) % MOD;  // 返回答案：选 k 个相等位置 C(n-1, k)，首元素 m 种，其余 n - 1 - k 个位置各 m - 1 种
    }
};