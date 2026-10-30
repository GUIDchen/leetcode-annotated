// 题目：3125. 使得按位与结果为 0 的最大数字（Maximum Number That Makes Result of Bitwise AND Zero）
// 思路：取 n 的最高二进制位，把它及其以上全部清零、以下全部置 1，得到的数既最大又与 n 按位与为 0。
// 时间复杂度：O(1)，只做一次前导零计算；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxNumber(long long n) {  // 求满足 (n & x) == 0 的最大整数 x
        return (1LL << (63 - __builtin_clzll(n))) - 1;  // __builtin_clzll(n) 是 64 位下前导零的个数，63 减去它就是最高位下标；把最高位以下全置 1 即为答案
    }  // 结束 maxNumber 方法
};  // 结束 Solution 类