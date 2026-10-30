// 3855. 给定范围内 K 位数字之和 / Sum of K-Digit Numbers in a Range（困难）
// 核心思路：k 位数的每一位权重之和是 k 个 1 组成的十进制数 (10^k - 1) / 9；固定某一位取某个数字后，其余 k-1 位可任选（共 n^(k-1) 种），故总和 = 区间数字和 × n^(k-1) × (10^k - 1) ÷ 9，除法用费马小定理求逆元实现。
// 复杂度：时间 O(log k + log mod)（两次快速幂），空间 O(1)。
class Solution {  // 设计一个算法：求所有 k 位、每位取自 [l, r] 的整数之和
public:  // 对外接口区
    int sumOfNumbers(int l, int r, int k) {  // 返回所有满足条件的 k 位数之和，对 1e9+7 取模
        const int mod = 1'000'000'007;  // 取模常数

        long long n = 1LL * r - l + 1;  // 可选数字的个数 n = r - l + 1

        // 区间 [l, r] 的等差求和 (l + r) * n / 2
        long long sum = 1LL * (l + r) * n / 2 % mod;  // 先算出 sum = 区间数字和（对 mod 取余）

        // 固定某一位后其余 k - 1 位可任取：n^(k - 1)
        long long part1 = qpow(n % mod, k - 1, mod);  // part1 = n^(k - 1) mod mod

        // k 个 1 组成的十进制数：(10^k - 1) / 9
        long long part2 = (qpow(10, k, mod) - 1 + mod) % mod;  // part2 = 10^k - 1（加 mod 避免减法出现负数）

        // 费马小定理求 9 的逆元
        long long inv9 = qpow(9, mod - 2, mod);  // inv9 用来代替“除以 9”

        long long ans = sum;  // 答案从区间数字和开始
        ans = ans * part1 % mod;  // 乘上排列数 n^(k - 1)
        ans = ans * part2 % mod;  // 乘上位权之和 10^k - 1
        ans = ans * inv9 % mod;  // 乘上 9 的逆元，等价于除以 9

        return (int) ans;  // 转回 int 返回
    }  // 方法结束

private:  // 内部辅助函数区
    long long qpow(long long a, long long n, int mod) {  // 快速幂：计算 a^n mod mod
        long long ans = 1;  // 答案初始化为 1
        a %= mod;  // 底数先对 mod 取模，防止溢出
        while (n > 0) {  // 按二进制位从低到高处理指数
            if (n & 1) {  // 当前最低位为 1，把 a^(2^i) 乘进答案
                ans = ans * a % mod;  // 累乘当前位权
            }  // 位权判断结束
            a = a * a % mod;  // 底数自乘，指数翻倍
            n >>= 1;  // 指数右移一位
        }  // 幂运算循环结束
        return ans;  // 返回 a^n mod mod
    }  // 辅助方法结束
};  // 类结束
