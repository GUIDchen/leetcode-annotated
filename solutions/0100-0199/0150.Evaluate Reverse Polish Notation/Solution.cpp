// 题目：150. 逆波兰表达式求值（Evaluate Reverse Polish Notation）
// 思路：后缀表达式用栈求值——遇到操作数就入栈，遇到运算符就弹出右、左操作数算完再压回。
// 时间复杂度：O(n)，每个 token 只处理一次；空间复杂度：O(n)，栈最多存 n/2 个操作数。
class Solution {  // 题目要求的题解类
public:  // 对外提供 evalRPN 方法
    int evalRPN(vector<string>& tokens) {  // tokens 是后缀表达式，返回求值结果
        stack<int> stk;  // 运算数栈
        for (auto& t : tokens) {  // 从左到右扫描每个 token
            if (t.size() > 1 || isdigit(t[0])) {  // 长度大于 1 或首字符是数字，说明（可能带负号的）操作数
                stk.push(stoi(t));  // 字符串转整数后入栈
            } else {  // 否则这个 token 是运算符
                int y = stk.top();  // 先弹出的是右操作数
                stk.pop();  // 弹出栈顶
                int x = stk.top();  // 后弹出的是左操作数
                stk.pop();  // 弹出栈顶
                if (t[0] == '+')  // 加法：结果压回栈中
                    stk.push(x + y);  // 压入 x + y
                else if (t[0] == '-')  // 减法：注意顺序是 x - y
                    stk.push(x - y);  // 压入 x - y
                else if (t[0] == '*')  // 乘法：结果压回栈中
                    stk.push(x * y);  // 压入 x * y
                else  // 剩下只可能是除法
                    stk.push(x / y);  // C++ 整数除法向零截断，与题目要求一致
            }  // 分支结束
        }
        return stk.top();  // 全部 token 处理完，栈顶就是整个表达式的值
    }  // evalRPN 方法结束
};  // Solution 类定义结束