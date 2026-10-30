// 题目：3094. 使用按位查询猜测数字 II（Guess the Number Using Bitwise Questions II）
// 思路：commonBits(num) 会先统计 n 与 num 相同二进制位的个数，再执行 n ^= num 永久改写 n；对同一个 1<<i 连问两次正好把 n 变回原值，比较两次计数即可判断第 i 位原本是否为 1。
// 时间复杂度：O(log n)，只需 32 位各询问两次；空间复杂度：O(1)，只用了常数个变量。
/**
 * Definition of commonBits API.
 * int commonBits(int num);
 */

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findNumber() {  // 返回隐藏数字 n 的初始值
        int n = 0;  // 逐位重建出来的答案
        for (int i = 0; i < 32; ++i) {  // 枚举 32 个二进制位（题目只用到低 30 位，多问不会出错）
            int count1 = commonBits(1 << i);  // 第一次询问：此时 n 的第 i 位被翻转
            int count2 = commonBits(1 << i);  // 第二次询问：再异或一次把 n 复原，同时拿到翻转后的计数
            if (count1 > count2) {  // 翻转后相同位数变少，说明第 i 位原本是 1
                n |= 1 << i;  // 把第 i 位记为 1
            }
        }
        return n;  // 返回重建出的初始值
    }
};