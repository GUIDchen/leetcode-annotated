// 题目：1047. 删除字符串中的所有相邻重复项（Remove All Adjacent Duplicates In String）
// 思路：用 string 当字符栈，从左到右扫描；当前字符与栈顶相同则弹栈（成对删除），否则入栈。
// 时间复杂度：O(n)，每个字符最多入栈出栈一次；空间复杂度：O(n)，栈最多保存 n 个字符。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string removeDuplicates(string s) {  // s：输入字符串；返回删除相邻重复对后的结果
        string stk;  // 用 string 充当字符栈，back() 就是栈顶
        for (char c : s) {  // 从左到右扫描，保证新形成的相邻重复也能被发现
            if (!stk.empty() && stk[stk.size() - 1] == c) {  // 栈非空且栈顶与当前字符相同
                stk.pop_back();  // 弹出栈顶，相当于把这一对一起删掉
            } else {  // 不构成重复对，需要入栈
                stk += c;  // 当前字符入栈
            }  // 分支结束
        }  // 扫描结束
        return stk;  // 栈里剩下的字符就是最终结果
    }  // 方法结束
};  // 题解类结束