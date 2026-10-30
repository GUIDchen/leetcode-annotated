// 题目：8. 字符串转换整数 (atoi)（String to Integer (atoi)）
// 思路：跳过前导空格与一个正负号，然后逐位累加数字；每步用 INT_MAX/10 和末位阈值预判溢出并截断到 int 上下界。
// 时间复杂度：O(n)，只扫描一遍字符串；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int myAtoi(string s) {  // 按 atoi 规则把字符串转成 32 位整数
        int i = 0, n = s.size();  // i 为扫描下标，n 为长度，用于每一步的越界保护
        while (i < n && s[i] == ' ')  // 跳过前导空格（同时防止下标越界）
            ++i;  // 空格就右移一位

        int sign = 1;  // 符号位，默认正数
        if (i < n && (s[i] == '-' || s[i] == '+')) {  // 还有字符且是正负号时
            sign = s[i] == '-' ? -1 : 1;  // 确定符号
            ++i;  // 跨过符号字符
        }

        int res = 0;  // 数字部分累加器（只存绝对值）
        while (i < n && isdigit(s[i])) {  // 只在字符是数字时继续读取
            int digit = s[i] - '0';  // 字符转数字
            if (res > INT_MAX / 10 || (res == INT_MAX / 10 && digit > INT_MAX % 10)) {  // 预判拼接后是否溢出
                return sign == 1 ? INT_MAX : INT_MIN;  // 溢出则按符号返回边界值
            }
            res = res * 10 + digit;  // 安全地累加这一位
            ++i;  // 前进到下一位
        }
        return res * sign;  // 乘符号返回结果
    }
};
