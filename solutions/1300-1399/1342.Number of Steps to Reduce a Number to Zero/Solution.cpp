// 题目：1342. 将数字变成 0 的操作次数（Number of Steps to Reduce a Number to Zero）
// 思路：直接模拟。奇数就减 1，偶数就右移一位（等价于除以 2），每做一次操作计数加一，直到 num 变成 0。
// 时间复杂度：O(log n)，每两步至少让二进制长度减少一位；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfSteps(int num) {  // num 是待归零的非负整数
        int ans = 0;  // 记录操作次数
        while (num) {  // num 变成 0 之前一直循环
            num = num & 1 ? num - 1 : num >> 1;  // 奇数（最低位为 1）就减 1，偶数就右移一位即除以 2
            ++ans;  // 操作次数加一
        }  // 循环结束
        return ans;  // 返回总操作次数
    }  // 方法结束
};  // 类定义结束