// 题目：4092. 二进制位得分（Binary Digit Score）
// 思路：分别用 __builtin_popcount 求出 a、b 的二进制表示中 1 的个数 s1、s2；s1 >= s2 时得分为两者之积，否则为 s2 整除 s1。
// 时间复杂度：O(1)，两次 popcount 都是常数级操作；空间复杂度：O(1)，只用两个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int calculateScore(int a, int b) {  // a、b：两个待打分的非负整数；返回按题面规则算出的得分
        int s1 = __builtin_popcount(a);  // s1 是 a 的二进制表示中 1 的个数
        int s2 = __builtin_popcount(b);  // s2 是 b 的二进制表示中 1 的个数
        return s1 >= s2 ? s1 * s2 : s2 / s1;  // s1 不小于 s2 时取乘积，否则取 s2 整除 s1 的商
    }  // 方法结束
};  // 类定义结束