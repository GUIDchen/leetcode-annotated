// 题目：2220. 转换数字的最少位翻转次数（Minimum Bit Flips to Convert Number）
// 思路：start ^ goal 中为 1 的位就是两数不同的位，用内置 popcount 一次数出这些位的个数。
// 时间复杂度：O(1)，按机器字长做一次位计数；空间复杂度：O(1)，只用寄存器保存异或结果。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minBitFlips(int start, int goal) {  // start 与 goal 是两个整数，返回最少翻转次数
        return __builtin_popcount(start ^ goal);  // 先异或出不同的位，再统计其中 1 的个数
    }
};
