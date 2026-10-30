// 题目：476. 数字的补数（Number Complement）
// 思路：先求出 num 的二进制有效位数 len，构造同长度的全 1 掩码 (1<<len)-1，再与 num 异或即得按位取反结果。
// 时间复杂度：O(1)，只有常数次位运算；空间复杂度：O(1)，不使用额外存储。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findComplement(int num) {  // num 是待求补数的正整数，返回其二进制最高有效位以内各位取反的结果
        return num ^ ((1LL << (64 - __builtin_clzll(num))) - 1);  // 64-clzll 得到有效位数，把 1 左移该位数再减 1 得到全 1 掩码，异或即按位取反
    }
};