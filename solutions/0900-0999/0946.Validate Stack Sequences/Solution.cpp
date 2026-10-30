// 题目：946. 验证栈序列（Validate Stack Sequences）
// 思路：按 pushed 顺序入栈，每入一个就尽量按 popped 的顺序从栈顶弹出；最后看 popped 是否被完整走完。
// 时间复杂度：O(n)，每个元素入栈、出栈各至多一次；空间复杂度：O(n)，栈最多同时保存 n 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {  // pushed：入栈顺序；popped：待验证的出栈顺序
        stack<int> stk;  // 模拟用的栈，保存当前仍留在栈里的元素
        int i = 0;  // 指向 popped 中下一个应当被弹出的位置
        for (int x : pushed) {  // 按 pushed 的顺序依次把元素压栈
            stk.push(x);  // 当前元素入栈，这是模拟中唯一允许的入栈动作
            while (stk.size() && stk.top() == popped[i]) {  // 只有栈非空且栈顶正好是下一个期望值时，才允许连续弹出
                stk.pop();  // 执行一次出栈
                ++i;  // 期望值前进一位
            }
        }  // 入栈阶段结束；若还有元素没能弹出，i 就走不到末尾
        return i == popped.size();  // popped 被完整匹配说明该出栈序列确实合法
    }
};