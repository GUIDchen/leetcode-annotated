// 题目：8. 字符串转换整数 (atoi)（String to Integer (atoi)）
// 思路：先跳过前导空格、识别一个正负号，再逐位累加数字；每次拼接前用 INT_MAX/10 与末位阈值判断溢出并做截断。
// 时间复杂度：O(n)，字符串扫描一遍；空间复杂度：O(1)。
int myAtoi(char* s) {  // 把字符串 s 按 atoi 规则转成 32 位整数
    int i = 0;  // 扫描下标

    while (s[i] == ' ') {  // 跳过所有前导空格
        i++;  // 空格就右移一位
    }

    int sign = 1;  // 符号位，默认正数
    if (s[i] == '-' || s[i] == '+') {  // 出现正号或负号
        sign = (s[i] == '-') ? -1 : 1;  // 记录符号，'-' 为负、'+' 为正
        i++;  // 跳过符号字符，指向第一个数字
    }

    int res = 0;  // 累加结果（只存绝对值部分，最后再乘符号）
    while (isdigit(s[i])) {  // 连续读取数字字符，遇到非数字即停止
        int digit = s[i] - '0';  // 字符转数字
        if (res > INT_MAX / 10 || (res == INT_MAX / 10 && digit > INT_MAX % 10)) {  // 再拼接一位就会超出 int 范围
            return sign == 1 ? INT_MAX : INT_MIN;  // 溢出时按符号截断到 INT_MAX 或 INT_MIN
        }
        res = res * 10 + digit;  // 确认安全后拼接这一位
        i++;  // 处理下一位
    }

    return res * sign;  // 乘上符号得到最终答案（没读到数字时 res 为 0）
}
