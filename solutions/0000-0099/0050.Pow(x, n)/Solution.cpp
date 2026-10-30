// 题目：50. Pow(x, n)（Pow(x, n)）
// 思路：快速幂（二进制幂）。把指数按二进制拆成若干 2 的幂，逐位平方底数、按位累乘结果；负指数先取正算再取倒数。
// 时间复杂度：O(log |n|)，循环次数等于指数的二进制位数；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double myPow(double x, int n) {  // x 为底数，n 为整数指数（可能为负）
        auto qpow = [](double a, long long n) {  // 快速幂 lambda：a 为底数，n 为非负指数；用 long long 防止 -INT_MIN 溢出
            double ans = 1;  // 累计结果，乘法单位元
            for (; n; n >>= 1) {  // 每轮把指数右移一位（相当于除以 2），直到指数为 0
                if (n & 1) {  // 指数当前最低位为 1，说明这一份 a^(2^k) 需要乘进结果
                    ans *= a;  // 把当前的 a^(2^k) 累乘进答案
                }  // if 结束
                a *= a;  // 底数平方，得到下一位对应的 a^(2^(k+1))
            }  // for 结束
            return ans;  // 返回 a^n
        };  // lambda 定义结束
        return n >= 0 ? qpow(x, n) : 1 / qpow(x, -(long long) n);  // n 非负直接算；n 为负则先转 long long 取正再算，最后取倒数
    }  // myPow 结束
};  // 类定义结束