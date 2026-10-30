// 题目：1190. 反转每对括号间的子串（Reverse Substrings Between Each Pair of Parentheses）
// 思路：用一个字符串当栈，遇到右括号就把栈顶到左括号之间的内容依次弹出（弹出顺序天然逆序），再整体压回栈顶。
// 时间复杂度：O(n^2)，每个字符最多被弹入弹出各一次但字符串拼接可能搬移；空间复杂度：O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string reverseParentheses(string s) {  // s：合法的括号串，返回按括号规则反转后的字符串
        string stk;  // 用字符串当栈，栈里始终是「已经处理完」的前缀字符
        for (char& c : s) {  // 逐字符扫描输入
            if (c == ')') {  // 遇到右括号：需要把本层括号内的内容整体反转
                string t;  // t 暂存从栈顶弹出的、需要反转的一段
                while (stk.back() != '(') {  // 一直弹到左括号为止
                    t.push_back(stk.back());  // 逆序弹出就等于完成了一次反转
                    stk.pop_back();  // 弹出栈顶字符
                }  // 弹出循环结束
                stk.pop_back();  // 丢掉与之配对的左括号
                stk += t;  // 把反转后的内容接回栈顶
            } else {  // 左括号和普通字符都直接入栈
                stk.push_back(c);  // 普通字符或 '(' 入栈
            }  // 分支结束
        }  // 扫描结束
        return stk;  // 栈里剩下的内容就是最终结果
    }  // 方法结束
};  // 类定义结束