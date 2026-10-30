// 题目：1922. 统计好数字的数目（Count Good Numbers）
// 思路：数学 + 快速幂。长度为 n 的数字串中，偶数下标（0,2,4,…）有 5 种合法数字，奇数下标有 4 种，故答案为 5^ceil(n/2) * 4^floor(n/2) mod 1e9+7。
// 时间复杂度：O(log n)，两次快速幂；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countGoodNumbers(long long n) {  // n 是数字串长度，返回长度为 n 的好数字串个数（对 1e9+7 取模）
        const int mod = 1e9 + 7;  // 取模用的大质数
        auto qpow = [](long long x, long long n) -> long long {  // 局部快速幂 lambda：计算 x^n mod mod，返回 long long 防溢出
            long long res = 1;  // 结果初始为 1（乘法单位元）
            while (n) {  // 指数 n 还没有变成 0 就继续
                if ((n & 1) == 1) {  // 当前二进制最低位为 1，说明这一份幂需要乘进结果
                    res = res * x % mod;  // 把 x^(2^k) 累乘进结果并取模
                }  // 结束按位判断
                x = x * x % mod;  // 底数自乘，为下一位准备 x^(2^(k+1))
                n >>= 1;  // 指数右移一位（除以 2）
            }  // 结束快速幂循环
            return res;  // 返回 x^n mod mod
        };  // 结束 lambda 定义
        return qpow(5, (n + 1) >> 1) * qpow(4, n >> 1) % mod;  // 偶数位（共 ceil(n/2) 个）5 种选择，奇数位（共 floor(n/2) 个）4 种选择，相乘后取模
    }  // 方法结束
};  // 类定义结束