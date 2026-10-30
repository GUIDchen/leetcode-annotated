// 题目：2696. 删除子串后的字符串最小长度（Minimum String Length After Removing Substrings）
// 核心思路：用字符串当栈，边扫描边把栈顶与当前字符凑成 "AB" 或 "CD" 就成对消去；消去后可能又露出新的可消对，栈天然处理了这种连锁反应。
// 时间复杂度：O(n)，每个字符最多入栈、出栈各一次；空间复杂度：O(n)，栈最多保存 n 个字符。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minLength(string s) {  // s：只含 'A'、'B'、'C'、'D' 的字符串；返回无法再消去的最短长度
        string stk = " ";  // 用字符串模拟栈，先塞一个空格作哨兵，保证空栈时 back() 也不越界
        for (char& c : s) {  // 依次读入每个字符
            if ((c == 'B' && stk.back() == 'A') || (c == 'D' && stk.back() == 'C')) {  // 当前字符与栈顶恰好拼成 "AB" 或 "CD"，可以成对消去
                stk.pop_back();  // 消去栈顶那个字符；当前字符也直接丢弃，不入栈
            } else {  // 凑不成可消子串
                stk.push_back(c);  // 压栈，等待后面的字符与它配对
            }
        }
        return stk.size() - 1;  // 减掉开头那个哨兵空格，剩下的就是最终无法消去的最短长度
    }
};