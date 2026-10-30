// 题目：2169. 得到 0 的操作数（Count Operations to Obtain Zero）
// 思路：直接模拟题意，每步用较大数减去较小数并把计数器加一，直到其中一个数减到 0。
// 时间复杂度：O(num1 + num2)，最坏是辗转相减的步数；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countOperations(int num1, int num2) {  // num1、num2：两个非负整数；返回让其中一个变成 0 所需的操作次数
        int ans = 0;  // ans：操作计数器
        for (; num1 && num2; ++ans) {  // 两个数都非 0 时继续相减，每轮结束 ans 自增
            if (num1 >= num2) {  // num1 更大或相等，就以它为被减数
                num1 -= num2;  // 用 num2 去减 num1
            } else {  // 否则 num2 更小
                num2 -= num1;  // 用 num1 去减 num2
            }  // if/else 结束
        }  // 循环结束，此时至少有一个数已经是 0
        return ans;  // 返回累计的操作次数
    }  // 方法结束
};  // 类定义结束
