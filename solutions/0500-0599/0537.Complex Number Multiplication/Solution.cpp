// 题目：537. 复数乘法（Complex Number Multiplication）
// 思路：把两个字符串各解析成实部 a 与虚部 b，再按 (a1+b1i)(a2+b2i) = (a1a2-b1b2) + (a1b2+a2b1)i 直接算出结果。
// 时间复杂度：O(len1+len2)，只做两次线性解析；空间复杂度：O(len1+len2)，用于存放输出字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string complexNumberMultiply(string num1, string num2) {  // num1、num2 是形如 "a+bi" 的复数字符串，返回乘积的同种形式
        int a1, b1, a2, b2;  // a1、b1 存第一个复数的实部与虚部，a2、b2 存第二个复数的实部与虚部
        sscanf(num1.c_str(), "%d+%di", &a1, &b1);  // sscanf 按 "%d+%di" 模板从 num1 中取出 a1 与 b1
        sscanf(num2.c_str(), "%d+%di", &a2, &b2);  // 同样解析 num2，取出 a2 与 b2
        return to_string(a1 * a2 - b1 * b2) + "+" + to_string(a1 * b2 + a2 * b1) + "i";  // 实部 a1a2-b1b2、虚部 a1b2+a2b1，用 to_string 拼成 "实部+虚部i" 返回
    }
};