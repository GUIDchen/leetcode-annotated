// 题目：2544. 交替数字和（Alternating Digit Sum）
// 思路：转成字符串从最高位开始遍历，按 +、- 交替累加各位数字。
// 时间复杂度：O(log n)，即位数；空间复杂度：O(log n)，字符串占用的临时空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int alternateDigitSum(int n) {  // 按题目要求从最高位开始依次取正、负号
        int ans = 0, sign = 1;  // ans 累加结果；sign 是当前位的符号，最高位取正
        for (char c : to_string(n)) {  // 转成字符串后从高位到低位逐字符遍历
            int x = c - '0';  // 字符编码相减，还原出这位数字的值
            ans += sign * x;  // 按当前符号把这位数字计入答案
            sign *= -1;  // 符号取反，下一位换成相反符号
        }  // 结束遍历
        return ans;  // 返回交替数字和
    }  // 方法结束
};  // 类定义结束（源文件末尾无换行，保持原样）