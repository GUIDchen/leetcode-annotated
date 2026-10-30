// 题目：2939. 最大异或乘积（Maximum Xor Product）
// 思路：n 位以上的高位无法改变；低 n 位逐位看，两边相同就同时置 1，不同就把这一位补给当前较小的数，使两数尽量接近。
// 时间复杂度：O(n)，逐位处理 n 个二进制位；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumXorProduct(long long a, long long b, int n) {  // a、b：初始的两个数；n：可以改动的二进制位个数（低 n 位）
        const int mod = 1e9 + 7;  // mod：结果需要对 1e9+7 取模
        long long ax = (a >> n) << n, bx = (b >> n) << n;  // 先把低 n 位清零、保留高位：高位不受选择影响，是固定的基数
        for (int i = n - 1; ~i; --i) {  // 从高到低枚举低 n 位；~i 等价于 i >= 0
            int x = a >> i & 1, y = b >> i & 1;  // 取出 a、b 在第 i 位的原始比特
            if (x == y) {  // 原始两位相同：无论怎么选，两边都能同时得到 1
                ax |= 1LL << i;  // 给 ax 的第 i 位置 1
                bx |= 1LL << i;  // 给 bx 的第 i 位置 1，两边同时变大，乘积跟着变大
            } else if (ax < bx) {  // 原始两位不同且 ax 更小：把这一位补给 ax 以拉近两者
                ax |= 1LL << i;  // ax 第 i 位置 1，让较小的它追上来
            } else {  // 其余情况即 bx 更小，把这一位补给 bx
                bx |= 1LL << i;  // bx 第 i 位置 1，让较小的它追上来
            }  // 分支结束
        }  // 逐位枚举结束
        ax %= mod;  // 先对 ax 取模，避免后面乘法溢出
        bx %= mod;  // 同理对 bx 取模
        return ax * bx % mod;  // 取模后的两数相乘再取模，得到最终答案
    }  // 方法结束
};  // 类定义结束