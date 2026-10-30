// 题目：461. 汉明距离（Hamming Distance）
// 思路：两个数的二进制表示中不同的位，在异或结果里恰好是 1；统计异或结果中 1 的个数即可。
// 时间复杂度：O(1)（最多检查 32 个二进制位）；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int hammingDistance(int x, int y) {  // x、y 是两个整数，统计它们二进制表示中不同位的个数
        return __builtin_popcount(x ^ y);  // 异或后不同的位变成 1，__builtin_popcount 统计其中 1 的个数
    }  // 结束方法
};