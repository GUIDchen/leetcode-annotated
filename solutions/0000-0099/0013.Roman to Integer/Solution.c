// 题目：13. 罗马数字转整数（Roman to Integer）
// 思路：从右往左（或等价地逐位比较相邻字符）累加；若左边字符比右边小说明它是减法组合，该位取负号。
// 时间复杂度：O(n)，n 为字符串长度，仅一次线性扫描；空间复杂度：O(1)，只用常数个变量。
int nums(char c) {  // 把单个罗马字符映射成它代表的基础数值
    switch (c) {  // 七个基本符号各自对应一个数值
    case 'I': return 1;  // I 表示 1
    case 'V': return 5;  // V 表示 5
    case 'X': return 10;  // X 表示 10
    case 'L': return 50;  // L 表示 50
    case 'C': return 100;  // C 表示 100
    case 'D': return 500;  // D 表示 500
    case 'M': return 1000;  // M 表示 1000
    default: return 0;  // 理论上不会出现其他字符，返回 0 兜底
    }
}

int romanToInt(char* s) {  // s 是合法的罗马数字字符串
    int ans = nums(s[strlen(s) - 1]);  // 最右边一位一定取正号，先计入答案作为基准
    for (int i = 0; i < (int) strlen(s) - 1; ++i) {  // 从最左位扫到倒数第二位，与它的右邻比较
        int sign = nums(s[i]) < nums(s[i + 1]) ? -1 : 1;  // 比右邻小说明构成 IV/IX 之类的减法组合，取负号
        ans += sign * nums(s[i]);  // 按符号累加当前位的数值
    }
    return ans;  // 返回换算出的整数
}
