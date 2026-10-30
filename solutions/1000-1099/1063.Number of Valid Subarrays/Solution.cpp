// 题目：1063. 有效子数组的数目（Number of Valid Subarrays）
// 思路：单调栈从右往左求每个下标右侧第一个更小元素的位置 right[i]，以 i 开头的有效子数组恰有 right[i] - i 个。
// 时间复杂度：O(n)，每个下标最多入栈出栈各一次；空间复杂度：O(n)，right 数组与栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int validSubarrays(vector<int>& nums) {  // nums：输入数组；返回满足「最左元素最小」的子数组个数
        int n = nums.size();  // 数组长度
        vector<int> right(n, n);  // right[i]：i 右侧第一个严格更小元素的下标；右侧没有更小元素时用哨兵 n
        stack<int> stk;  // 单调栈，存下标，从栈底到栈顶对应的数值单调不减
        for (int i = n - 1; ~i; --i) {  // 从右往左枚举；~i 等价于 i >= 0，i 变成 -1 时 ~(-1) == 0 退出
            while (stk.size() && nums[stk.top()] >= nums[i]) {  // 栈顶数值不严格更小，它不可能成为 i 的右侧第一个更小元素，直接弹出
                stk.pop();  // 弹出被淘汰的下标
            }  // end while：栈顶已严格小于 nums[i] 或栈空
            if (stk.size()) {  // 栈非空说明找到了 i 的右侧第一个更小元素
                right[i] = stk.top();  // 记下这个位置，它决定以 i 开头的子数组右端点上限
            }  // end if
            stk.push(i);  // 当前下标入栈，供更左侧的元素当作「右侧第一个更小元素」的候选
        }  // end for：right 数组计算完毕
        int ans = 0;  // 有效子数组总数
        for (int i = 0; i < n; ++i) {  // 枚举每个起点
            ans += right[i] - i;  // 起点固定为 i 时，终点取 i..right[i]-1 都满足最小值在左端，共 right[i] - i 个
        }  // end for
        return ans;  // 返回有效子数组总数
    }  // end method
};  // end class