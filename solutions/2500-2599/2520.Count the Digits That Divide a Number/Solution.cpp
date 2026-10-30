// 题目：2520. 统计能整除数字的位数（Count the Digits That Divide a Number）
// 核心思路：用循环逐位取 num 的最低位数，判断 num 能否被该位数字整除，能整除则计数加一。
// 时间复杂度：O(log num)，即 num 的位数；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解接口对外可见
    int countDigits(int num) {  // num：待统计的整数；返回其中能整除 num 的位数
        int ans = 0;  // ans 记录满足条件的位数
        for (int x = num; x > 0; x /= 10) {  // x 从 num 开始，每轮丢掉最低位，直到为 0
            if (num % (x % 10) == 0) {  // x % 10 是当前最低位数字，判断它能否整除 num
                ++ans;  // 能整除，计数加一
            }  // 结束 if
        }  // 结束 for
        return ans;  // 返回能整除 num 的位数
    }  // 结束 countDigits
};  // 结束 Solution 类