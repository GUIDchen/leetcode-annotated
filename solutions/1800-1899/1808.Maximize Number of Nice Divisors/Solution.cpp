// 题目：1808. 好因子的最大数目（Maximize Number of Nice Divisors）
// 思路：把质因子尽量拆成 3 相乘最优；余 1 时改成 2+2（少一个 3 乘 4），余 2 时再乘一个 2，用快速幂取模。
// 时间复杂度：O(log n)，快速幂对指数做二进制拆分；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxNiceDivisors(int primeFactors) {  // primeFactors：可用的质因子个数（把这些质因子相乘凑成一个数 n）
        if (primeFactors < 4) {  // 规模很小时不再拆分更划算
            return primeFactors;  // 1、2、3 的最优值都是它自己
        }  // if 结束
        const int mod = 1e9 + 7;  // 模数 1e9 + 7，所有中间结果都要取模防止溢出
        auto qpow = [&](long long a, long long n) {  // 快速幂的局部 lambda：计算 a 的 n 次方再对 mod 取模
            long long ans = 1;  // ans 保存累乘结果，初始为 1
            for (; n; n >>= 1) {  // 逐位从低到高处理指数，n 变成 0 时结束
                if (n & 1) {  // 当前二进制位是 1
                    ans = ans * a % mod;  // 把 a 的对应次幂累乘进答案
                }  // if 结束
                a = a * a % mod;  // a 自乘即平方，对应指数翻倍
            }  // for 结束
            return (int) ans;  // 转回 int 返回（结果已小于 mod）
        };  // lambda 定义结束
        if (primeFactors % 3 == 0) {  // 能被 3 整除：全部拆成 3
            return qpow(3, primeFactors / 3);  // 直接返回 3 的 (n/3) 次方
        }  // if 结束
        if (primeFactors % 3 == 1) {  // 除以 3 余 1：把最后的 3+1 换成 2+2 更优
            return qpow(3, primeFactors / 3 - 1) * 4L % mod;  // 少用一个 3，再多乘一个 4，对应 2 * 2
        }  // if 结束
        return qpow(3, primeFactors / 3) * 2 % mod;  // 除以 3 余 2：直接再多乘一个因子 2
    }  // 方法结束
};  // 类定义结束