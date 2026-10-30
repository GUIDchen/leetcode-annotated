// 题目：439. 三元表达式解析器（Ternary Expression Parser）
// 思路：从右往左扫描表达式，用栈暂存操作数；遇到 '?' 后按条件的 T/F 只保留真值或假值分支，遇到 ':' 直接跳过。
// 复杂度：时间复杂度 O(n)，每个字符只处理一次；空间复杂度 O(n)，栈最多保存 n 个字符。
class Solution {  // 题解类：负责解析三元表达式
public:  // 公开部分：LeetCode 只调用下面的 parseTernary
    string parseTernary(string expression) {  // expression 是形如 'T?2:3' 的表达式，返回最终结果的单个字符
        string stk;  // 用一个 string 当栈，从右往左扫描时暂存操作数与中间结果
        bool cond = false;  // 标记刚读到的 '?' 是否还没有被它的冒号分支消费掉
        reverse(expression.begin(), expression.end());  // 倒序处理字符串，让最内层的三元式最先被化简
        for (char& c : expression) {  // 从左到右遍历倒序后的字符，等价于在原串上从右往左扫描
            if (c == ':') {  // ':' 只是分支分隔符，本身不含任何运算信息
                continue;  // 直接跳过，继续看下一个字符
            }  // 闭合上一层的 if (c == ':')
            if (c == '?') {  // 遇到 '?'：说明它的条件字符已经在栈顶等着求值了
                cond = true;  // 置位标记，下一次读到的字符就是条件 T/F
            } else {  // 否则当前字符是普通字符：可能是条件 T/F，也可能是操作数
                if (cond) {  // cond 为真说明刚读到的是 '?' 后面的条件字符
                    if (c == 'T') {  // 条件为真：保留真值分支，丢弃假值分支
                        char x = stk.back();  // 先取出栈顶，也就是真值分支的结果
                        stk.pop_back();  // 弹出真值分支（值已经保存在 x 中）
                        stk.pop_back();  // 再弹出一个，即被丢弃的假值分支
                        stk.push_back(x);  // 把真值分支结果压回栈，它就是整个三元式的结果
                    } else {  // 否则条件为假：只保留假值分支
                        stk.pop_back();  // 弹出真值分支，让假值分支留在栈顶作为结果
                    }  // 闭合 else
                    cond = false;  // 这个 '?' 已经处理完毕，清除标记
                } else {  // 否则当前字符是普通操作数
                    stk.push_back(c);  // 操作数直接入栈，等待外层的三元运算使用
                }  // 闭合内层 else
            }  // 闭合外层 else
        }  // 扫描结束，所有三元式都已化简成单个字符
        return {stk[0]};  // 栈里只剩最终答案，取出返回
    }  // parseTernary 方法结束
};  // Solution 类定义结束