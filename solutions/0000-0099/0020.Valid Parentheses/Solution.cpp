// 题目：20. 有效的括号（Valid Parentheses）
// 思路：用栈保存「之后必须出现的右括号」；遇左括号压入配对的右括号，遇右括号则必须与栈顶相同。
// 时间复杂度：O(n)，每个字符最多进出栈各一次；空间复杂度：O(n)，栈最坏存放 n 个字符。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isValid(string s) {  // s：只由 ()[]{} 组成的括号串
        string stk;  // 用 string 当栈：push_back 入栈、back 看栈顶、pop_back 出栈
        unordered_map<char, char> d{{'(', ')'}, {'[', ']'}, {'{', '}'}};  // 映射表：左括号 → 与之配对的右括号
        for (char c : s) {  // 从左到右依次扫描每个字符
            if (d.contains(c)) {  // C++20 的 contains：c 是左括号（在映射表的键里）
                stk.push_back(d[c]);  // 把「接下来必须出现的右括号」压入栈，等待后续匹配
            } else if (stk.empty() || stk.back() != c) {  // 遇到右括号，但栈空（无左括号可配）或栈顶不是它
                return false;  // 括号序列不合法
            } else {  // 栈顶正是与该右括号配对的那一项
                stk.pop_back();  // 弹出，表示这一对已经匹配
            }
        }
        return stk.empty();  // 全部匹配完栈应为空；非空说明还有左括号没闭合
    }
};
