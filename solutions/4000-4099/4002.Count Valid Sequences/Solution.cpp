// 4002. 统计有效序列数目 / Count Valid Sequences（中等）
// 核心思路：长度为 k、和为 n 的正整数序列用隔板法共 C(n-1, k-1) 个；乘积为奇数等价于每个数都是奇数，这类序列有 C((n+k)/2 - 1, k-1) 个（仅当 n+k 为偶数时存在），容斥相减即得乘积为偶数的方案数。
// 复杂度：预处理 O(MX log MOD) 时间与 O(MX) 空间，单次查询 O(1)。
const int MX = 500001;  // 预处理规模：n 最大 5 * 10^5
const long long MOD = 1000000007LL;  // 组合数取模用的模数

long long f[MX];  // f[i] 将存放 i! % MOD
long long g[MX];  // g[i] 将存放 (i!)^(MOD-2) % MOD，即阶乘的模逆元

long long qpow(long long a, long long b) {  // 快速幂：返回 a^b % MOD
    long long res = 1;  // 幂的累积结果
    while (b > 0) {  // 按指数的二进制位迭代
        if (b & 1) {  // 当前最低位为 1
            res = res * a % MOD;  // 把这一位对应的幂乘进结果
        }  // if 结束
        a = a * a % MOD;  // 底数平方，对应指数左移一位
        b >>= 1;  // 指数右移一位
    }  // while 结束
    return res;  // 返回 a^b % MOD
}  // 函数结束

int init = []() {  // 静态初始化：程序启动时预先算出阶乘与阶乘逆元
    f[0] = 1;  // 0! = 1
    g[0] = 1;  // 0! 的逆元也是 1

    for (int i = 1; i < MX; i++) {  // 从小到大递推
        f[i] = f[i - 1] * i % MOD;  // 递推阶乘
        g[i] = qpow(f[i], MOD - 2);  // 费马小定理求阶乘逆元
    }  // for 结束

    return 0;  // 返回 0，仅为满足 lambda 的返回类型
}();  // 立即执行该 lambda，结果赋给 init

long long comb(int n, int k) {  // 组合数 C(n, k) % MOD
    return f[n] * g[k] % MOD * g[n - k] % MOD;  // n! / (k! (n-k)!)，用逆元相乘代替除法
}  // 函数结束

class Solution {  // 题解类
public:  // 公有接口
    int countValidSequences(int n, int k) {  // 返回长度为 k、和为 n 且乘积为偶数的序列个数
        long long ans = comb(n - 1, k - 1);  // 隔板法：忽略奇偶性限制的全部序列数

        if ((n + k) % 2 == 0) {  // 只有 n+k 为偶数时，才存在「全为奇数」的序列
            ans = (ans - comb((n + k) / 2 - 1, k - 1) + MOD) % MOD;  // 容斥减去乘积为奇数（全为奇数）的方案，+ MOD 防止出现负数
        }  // if 结束

        return (int) ans;  // 转回 int 返回答案
    }  // 方法结束
};  // 类定义结束