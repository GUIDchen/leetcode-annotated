// 题目：504. 七进制数（Base 7）
// 思路：不断对 7 取余得到最低位、整除 7 去掉最低位；0 与负数单独处理，负数递归成 -convertToBase7(-num)。
// 时间复杂度：O(log_7 |num|)；空间复杂度：O(log_7 |num|)，用于存放结果字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string convertToBase7(int num) {  // num：待转换的十进制整数；返回其七进制字符串
        if (num == 0) return "0";  // 0 单独处理，否则下面的 while 一次都不执行，会返回空串
        if (num < 0) return "-" + convertToBase7(-num);  // 负数先递归求相反数的七进制，再在最前面补负号
        string ans = "";  // 用字符串累积七进制结果
        while (num) {  // 反复取余、整除，直到 num 变成 0
            ans = to_string(num % 7) + ans;  // 余数是当前最低位，拼到结果最前面（逆序累积）
            num /= 7;  // 去掉已经处理的最低位
        }  // 循环结束，ans 就是 num 的七进制表示
        return ans;  // 返回七进制字符串
    }  // 方法结束
};  // 类定义结束