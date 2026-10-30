// 题目：739. 每日温度（Daily Temperatures）
// 思路：从右往左维护一个「温度严格递减」的下标单调栈，栈顶就是右侧第一个比当前温度更高的日子，可直接算出等待天数。
// 时间复杂度：O(n)，每个下标最多入栈、出栈各一次；空间复杂度：O(n)，栈与答案数组各占 O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> dailyTemperatures(vector<int>& temperatures) {  // temperatures：每天的温度数组，返回每天需要等待的天数
        int n = temperatures.size();  // 总天数
        stack<int> stk;  // 单调栈，存下标；从栈底到栈顶对应的温度严格递减
        vector<int> ans(n);  // 答案数组：默认 0 表示之后没有更高温度
        for (int i = n - 1; ~i; --i) {  // 从最后一天往前扫；~i 即 i != -1，等于 -1 时结束
            while (!stk.empty() && temperatures[stk.top()] <= temperatures[i]) {  // 栈顶温度不高于当前温度，它不可能再成为任何更左位置的「第一个更高日」，直接弹出
                stk.pop();  // 弹出被淘汰的下标
            }  // 结束 while
            if (!stk.empty()) {  // 栈非空说明存在右侧第一个更高温度
                ans[i] = stk.top() - i;  // 栈顶下标减当前下标就是需要等待的天数
            }  // 结束 if
            stk.push(i);  // 当前下标入栈，成为更左位置的候选
        }  // 结束 for
        return ans;  // 返回每天的等待天数
    }  // 结束 dailyTemperatures
};  // 结束 Solution 类
