// 题目：2235. 两整数相加（Add Two Integers）
// 思路：直接用加法运算符返回两个整数之和。
// 时间复杂度：O(1)；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int sum(int num1, int num2) {  // num1、num2 为待相加的两个整数
        return num1 + num2;  // 直接相加并返回结果
    }  // 结束 sum 方法
};  // 结束 Solution 类