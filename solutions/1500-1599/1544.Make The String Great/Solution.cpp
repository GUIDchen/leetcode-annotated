// 题目：1544. 整理字符串（Make The String Great）
// 思路：用栈模拟消除过程，当前字符与栈顶是同一个字母的大小写（ASCII 相差 32）就一起消掉，否则入栈。
// 时间复杂度：O(n)，每个字符至多进出栈一次；空间复杂度：O(n)，栈最坏存下整个字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string makeGood(string s) {  // s：待整理的字符串
        string stk;  // 用字符串当栈，栈顶就是 stk.back()
        for (char c : s) {  // 从左到右逐个处理字符
            if (stk.empty() || abs(stk.back() - c) != 32) {  // 栈空，或与栈顶不是同一字母的大小写（差值绝对值不是 32），当前字符需要入栈
                stk += c;  // 压入栈顶，等待与后面的字符配对
            } else {  // 否则当前字符与栈顶构成一组「坏对」
                stk.pop_back();  // 弹出栈顶，相当于把这两个字符一起消掉
            }
        }
        return stk;  // 栈里剩下的就是整理后的字符串
    }
};