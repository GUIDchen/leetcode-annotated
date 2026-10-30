// 题目：3174. 清除数字（Clear Digits）
// 思路：用字符串当栈从左到右扫描：字母入栈，遇到数字就弹出栈顶字母，相当于删除它左边最近的字母。
// 时间复杂度：O(n)，每个字符最多进出栈各一次；空间复杂度：O(n)，栈最多保存 n 个字符。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string clearDigits(string s) {  // s 是小写字母与数字混合的字符串，返回清除所有数字后的字符串
        string stk;  // 用 string 充当栈，保存还没被数字删掉的字母
        for (char c : s) {  // 从左到右扫描每个字符
            if (isdigit(c)) {  // 当前字符是数字
                stk.pop_back();  // 数字要连带删掉它左边最近的字母，也就是栈顶，题目保证此时栈非空
            } else {  // 否则是字母，入栈保留下来
                stk.push_back(c);  // 字母入栈，等待后面可能出现的数字把它删掉
            }
        }
        return stk;  // 栈里剩下的字符就是清除数字后的结果
    }
};