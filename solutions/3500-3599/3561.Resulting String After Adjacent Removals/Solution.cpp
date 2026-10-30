// 3561. 移除相邻字符 / Resulting String After Adjacent Removals
// 核心思路：用栈模拟删除过程，若栈顶字符与当前字符的字母序号差为 1 或 25（即相邻或首尾相邻）则弹出栈顶，否则把当前字符入栈。
// 复杂度：时间 O(n)，空间 O(n)
class Solution {  // 定义解题类
public:  // 公有接口
    string resultingString(string s) {  // 返回反复删除相邻的“循环相邻”字符后剩下的字符串
        string stk;  // 用栈保存尚未被删除的字符
        for (char c : s) {  // 从左到右扫描字符串
            if (stk.size() && (abs(stk.back() - c) == 1 || abs(stk.back() - c) == 25)) {  // 栈顶与当前字符相邻或跨越 z/a 相邻时可以删除
                stk.pop_back();  // 弹出栈顶，相当于把这一对字符删掉
            } else {  // 不能删除时
                stk.push_back(c);  // 当前字符入栈
            }  // 结束能否删除的判断
        }  // 结束扫描
        return stk;  // 栈中剩下的字符就是结果
    }  // 结束 resultingString
};  // 结束类定义