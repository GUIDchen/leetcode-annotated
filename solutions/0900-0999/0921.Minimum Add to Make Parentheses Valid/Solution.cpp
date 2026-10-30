// 题目：921. 使括号有效的最少添加（Minimum Add to Make Parentheses Valid）
// 思路：用栈抵消配对的括号，最后栈里剩下的未匹配括号个数就是最少需要添加的个数。
// 时间复杂度：O(n)，每个字符进出栈至多一次；空间复杂度：O(n)，栈最多存 n 个字符。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minAddToMakeValid(string s) {  // s 是只含 '(' 与 ')' 的字符串
        string stk;  // 用字符串当栈，只保存尚未匹配的括号
        for (char c : s) {  // 逐个扫描字符
            if (c == ')' && stk.size() && stk.back() == '(')  // 右括号且栈顶是左括号，说明这一对可以匹配
                stk.pop_back();  // 弹出已匹配的左括号
            else  // 其他情况：左括号，或暂时无法匹配的右括号
                stk.push_back(c);  // 压栈，留给后续字符匹配
        }  // 结束遍历
        return stk.size();  // 栈里剩下的每个括号都要各补一个配对，故个数就是答案
    }  // 结束 minAddToMakeValid 方法
};  // 结束 Solution 类