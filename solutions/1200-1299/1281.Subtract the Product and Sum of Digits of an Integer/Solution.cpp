// 题目：1281. 整数的各位积和之差（Subtract the Product and Sum of Digits of an Integer）
// 思路：循环取最低位数字，同时累乘到积、累加到和，最后用积减和。
// 时间复杂度：O(log n)，循环次数等于十进制位数；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int subtractProductAndSum(int n) {  // 输入整数 n，返回各位数字之积减去各位数字之和
        int x = 1, y = 0;  // x 是各位数字的乘积（初始 1），y 是各位数字之和（初始 0）
        for (; n; n /= 10) {  // n 非 0 就继续；每轮末尾整除 10 去掉最低位
            int v = n % 10;  // 取出当前最低位数字
            x *= v;  // 把这一位乘入积中
            y += v;  // 把这一位加入和中
        }
        return x - y;  // 返回各位数字之积与各位数字之和的差
    }
};  // 题解类定义结束（本文件末尾无换行，已保留）