// 题目：2550. 猴子碰撞的方法数（Count Collisions of Monkeys on a Polygon）
// 思路：容斥。每只猴子 2 种走法，共 2^n 种；不碰撞只有「全部顺时针」和「全部逆时针」2 种，所以答案是 2^n - 2（取模）。
// 时间复杂度：O(log n)，快速幂逐位平方；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int monkeyMove(int n) {  // n 是猴子个数，也就是多边形的顶点数
        const int mod = 1e9 + 7;  // 按题目要求对 1e9+7 取模
        using ll = long long;  // 用 long long 承载中间乘积，避免快速幂里 a * a 溢出
        auto qpow = [&](ll a, int n) {  // qpow：快速幂，计算 a 的 n 次方（模 mod）
            ll ans = 1;  // ans 是累乘结果，从 1 开始
            for (; n; n >>= 1) {  // 逐位处理指数：每轮把 n 右移一位，直到 n 变成 0
                if (n & 1) {  // 当前最低位为 1 时，本轮的 a 要乘进答案
                    ans = ans * a % mod;  // 累乘并取模
                }
                a = a * a % mod;  // 底数自乘平方，为下一位指数做准备
            }
            return ans;  // 返回 a^n mod mod
        };  // lambda 定义结束，下一行即可调用 qpow
        return (qpow(2, n) - 2 + mod) % mod;  // 总方案 2^n 减去两种全同向（不碰撞）方案，+mod 防止减成负数
    }
};