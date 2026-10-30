// 题目：866. 回文质数（Prime Palindrome）
// 思路：从 n 起逐个向上枚举，同时判回文与判质数（试除法到 sqrt）；8 位回文数必是 11 的倍数，故跳过 [10^7, 10^8) 区间。
// 时间复杂度：O(枚举个数 × sqrt(当前值))；空间复杂度：O(1)，只用了常数个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int primePalindrome(int n) {  // 返回大于等于 n 的最小回文质数
        while (1) {  // 从小到大逐个枚举，命中即返回，所以用死循环
            if (reverse(n) == n && isPrime(n)) return n;  // 先判回文再判质数，两者都成立才是答案
            if (n > 10000000 && n < 100000000) n = 100000000;  // 8 位回文数一定能被 11 整除，不可能是质数，直接跳到 10^8
            ++n;  // 否则只需继续检查下一个整数
        }
    }  // 循环内部已经 return，函数实际不会执行到这里

    bool isPrime(int x) {  // 试除法判断 x 是否为质数
        if (x < 2) return false;  // 小于 2 的数（0、1 和负数）都不是质数
        for (int v = 2; v * v <= x; ++v)  // 只需试除到 sqrt(x)，用 v*v<=x 避免开方的浮点误差
            if (x % v == 0)  // 找到一个因子就说明 x 是合数
                return false;  // 立即返回 false，不再继续试除
        return true;  // 试除完毕没有因子，x 是质数
    }

    int reverse(int x) {  // 把十进制数字反转，用于回文判断
        int res = 0;  // res 记录反转后的数值
        while (x) {  // 不断取下 x 的末位，直到 x 变为 0
            res = res * 10 + x % 10;  // 把末位接到 res 尾部，相当于十进制左移一位再加末位
            x /= 10;  // 整除 10 去掉刚处理过的末位
        }
        return res;  // 返回反转结果
    }
};  // 题解类定义结束