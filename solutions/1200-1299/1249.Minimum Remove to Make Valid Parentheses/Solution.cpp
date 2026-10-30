// 题目：1249. 移除无效的括号（Minimum Remove to Make Valid Parentheses）
// 思路：两遍扫描 —— 先从左往右删掉多余的右括号，再从右往左删掉多余的左括号，最后翻转得到结果。
// 时间复杂度：O(n)，两遍线性扫描；空间复杂度：O(n)，用于存中间结果与答案。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法入口
    string minRemoveToMakeValid(string s) {  // 删除最少数量的括号，使剩下的字符串括号合法
        string stk;  // 用 string 当栈，保存正向扫描后保留下来的字符
        int x = 0;  // 当前还未匹配的左括号数量
        for (char& c : s) {  // 从左往右扫描每个字符
            if (c == ')' && x == 0) continue;  // 没有左括号可以配对的右括号，必须删除
            if (c == '(')  // 左括号
                ++x;  // 待匹配的左括号加一
            else if (c == ')')  // 右括号
                --x;  // 与一个左括号配对，待匹配数减一
            stk.push_back(c);  // 保留该字符
        }
        string ans;  // 反向扫描得到的结果（此时是逆序）
        x = 0;  // 复用计数器，这一遍统计未匹配的右括号
        while (stk.size()) {  // 从尾部往前处理剩下的字符
            char c = stk.back();  // 取最后一个字符
            stk.pop_back();  // 弹出它
            if (c == '(' && x == 0) continue;  // 没有右括号可配对的左括号，必须删除
            if (c == ')')  // 右括号
                ++x;  // 待匹配的右括号加一
            else if (c == '(')  // 左括号
                --x;  // 与一个右括号配对，待匹配数减一
            ans.push_back(c);  // 保留该字符
        }
        reverse(ans.begin(), ans.end());  // 逆序收集的答案再翻转回正序
        return ans;  // 返回删除最少括号后的合法字符串
    }
};  // 类定义结束