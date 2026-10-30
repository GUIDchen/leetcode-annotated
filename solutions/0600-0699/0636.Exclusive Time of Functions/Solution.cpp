// 题目：636. 函数的独占时间（Exclusive Time of Functions）
// 思路：用栈模拟调用关系：遇到 start 先把栈顶函数这段时间结算、再压栈；遇到 end 弹栈并结算，end 的时间点要 +1 因为区间闭合。
// 时间复杂度：O(L)，L 为日志条数；空间复杂度：O(n)，栈深最多 n。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> exclusiveTime(int n, vector<string>& logs) {  // n 是函数个数，logs 是按时间排列的调用日志，返回每个函数的独占时间
        vector<int> ans(n);  // ans[i] 记录第 i 个函数的独占时间，初始为 0
        stack<int> stk;  // 调用栈，栈顶是当前正在执行的函数 id
        int pre = 0;  // 下一个待结算的时间点（上一段已经算到 pre 之前）
        for (const auto& log : logs) {  // 按时间顺序处理每条日志
            int i, cur;  // i 是函数 id，cur 是这条日志的时间戳
            char c[10];  // 存放操作名 start / end 的字符缓冲区
            sscanf(log.c_str(), "%d:%[^:]:%d", &i, c, &cur);  // 按 id:操作:时间 的格式切分日志；%[^:] 表示读到下一个冒号为止
            if (c[0] == 's') {  // 首字母是 s 说明是 start 日志
                if (stk.size()) {  // 栈非空说明此前有父函数正在执行，被子调用打断
                    ans[stk.top()] += cur - pre;  // 把 pre 到 cur 这段确定属于父函数的时间累加给它
                }  // 父函数结算结束
                stk.push(i);  // 当前函数开始执行，压栈成为新的栈顶
                pre = cur;  // 结算位置推进到本条日志的时间点
            } else {  // 否则是 end 日志
                ans[stk.top()] += cur - pre + 1;  // 栈顶函数从 pre 一直执行到 cur（含时间点 cur），所以要 +1
                stk.pop();  // 该函数执行完毕，出栈
                pre = cur + 1;  // 下一个时间点从 cur+1 开始，因为 cur 已被该函数占用
            }  // 分支结束
        }  // 所有日志处理完毕
        return ans;  // 返回每个函数的独占时间
    }  // 方法结束
};  // 类定义结束
