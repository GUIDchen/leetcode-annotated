// 题目：372. 超级次方（Super Pow）
// 思路：把大指数 b 按十进制位拆开，从最低位向左逐位累乘 a^(b[i])，每位之间把底数自乘 10 次（a ← a^10）；幂用快速幂并在 1337 下取模。
// 时间复杂度：O(len(b) · log 10)，快速幂只需约 4 次乘法；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int superPow(int a, vector<int>& b) {  // a：底数；b：以数组形式给出的大指数（高位在前）；结果对 1337 取模
        using ll = long long;  // 给 long long 起别名，防止乘法中间结果溢出
        const int mod = 1337;  // 题目指定的模数 1337（7 * 191）
        ll ans = 1;  // 累乘结果，从 1 开始
        auto qpow = [&](ll a, int n) {  // 快速幂 lambda：计算 a^n % mod，并用 [&] 捕获 mod
            ll ans = 1;  // 快速幂内部的累乘器
            for (; n; n >>= 1) {  // 逐位处理指数 n，每轮把 n 右移一位
                if (n & 1) {  // 当前最低位为 1 时，把这一份 a 乘进结果
                    ans = ans * a % mod;  // 乘入当前底数（取模控制规模）
                }  // if 分支闭合
                a = a * a % mod;  // 底数平方，为下一位做准备（取模控制规模）
            }  // 指数位处理完毕
            return (int) ans;  // 转回 int 返回（结果一定小于 1337）
        };  // lambda 定义结束
        for (int i = b.size() - 1; ~i; --i) {  // 从 b 的最低位（数组末尾）开始向左处理；~i 等价于 i >= 0
            ans = ans * qpow(a, b[i]) % mod;  // 把 a^(b[i]) 这一份乘进总结果
            a = qpow(a, 10);  // 处理完这一位后底数变成 a^10，供高一位使用
        }  // 逐位循环闭合
        return ans;  // 返回 a^b mod 1337
    }  // 方法结束
};  // 类定义结束