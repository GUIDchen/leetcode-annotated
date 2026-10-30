// 题目：2496. 数组中字符串的最大值（Maximum Value of a String in an Array）
// 思路：单个字符串的值 = 纯数字串的数值，或含字母时取字符串长度；逐个换算再取最大。
// 时间复杂度：O(所有字符总数)；空间复杂度：O(1)，只用常数个变量。
#define max(a, b) (((a) > (b)) ? (a) : (b))  // 宏定义：C 标准库没有 max 函数，用三元表达式实现最大值

int parseInt(char* s) {  // 把字符串换算成题目定义的值：全数字取数值，含非数字取长度
    int n = strlen(s);  // 先记下长度，遇到非数字字符时直接用它当结果返回
    int res = 0;  // 数字部分的累加结果
    for (int i = 0; i < n; i++) {  // 逐字符扫描整个字符串
        if (!isdigit(s[i])) {  // 出现非数字字符
            return n;  // 按题意，含字母的字符串取「字符串长度」作为值
        }
        res = res * 10 + s[i] - '0';  // 十进制累加：旧值进一位再加上当前数字字符对应的值
    }
    return res;  // 全是数字，返回换算出的整数
}

int maximumValue(char** strs, int strsSize) {  // strs 是字符串数组，strsSize 是元素个数
    int ans = 0;  // 记录目前的最大值，初值取 0（字符串的值非负）
    for (int i = 0; i < strsSize; i++) {  // 逐个字符串处理
        int num = parseInt(strs[i]);  // 求当前字符串的值
        ans = max(ans, num);  // 用最大值宏更新答案
    }
    return ans;  // 返回整个数组中的最大值
}