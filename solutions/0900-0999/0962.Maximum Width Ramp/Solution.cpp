// 题目：962. 最大宽度坡（Maximum Width Ramp）
// 思路：先从左到右维护一个数值严格递减的下标单调栈作为候选左端点，再从右往左扫描，用最靠右的右端点去匹配栈顶，匹配成功就弹出并更新答案。
// 时间复杂度：O(n)，每个下标最多入栈、出栈各一次；空间复杂度：O(n)，单调栈最多保存 n 个下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxWidthRamp(vector<int>& nums) {  // nums：输入数组，返回满足 i<j 且 nums[i]<=nums[j] 的最大宽度 j-i
        int n = nums.size();  // n：数组长度
        stack<int> stk;  // 单调栈：保存下标，它们对应的值从栈底到栈顶严格递减
        for (int i = 0; i < n; ++i) {  // 从左到右扫描，收集所有可能成为左端点的下标
            if (stk.empty() || nums[stk.top()] > nums[i]) stk.push(i);  // 只有比栈顶值更小的位置才入栈，值更大的左端点不可能比栈顶给出更宽的坡
        }
        int ans = 0;  // ans：当前找到的最大宽度，初始为 0（坡可以宽度为 0）
        for (int i = n - 1; i; --i) {  // 从右往左扫描，把最靠右的位置当作右端点去匹配左端点
            while (!stk.empty() && nums[stk.top()] <= nums[i]) {  // 栈顶值不超过当前值，说明 (栈顶下标, i) 是一个合法坡
                ans = max(ans, i - stk.top());  // 用当前宽度更新答案
                stk.pop();  // 该左端点已经配到最靠右的合法右端点，不可能再更优，弹出
            }
            if (stk.empty()) break;  // 栈空了说明所有左端点都处理完，提前结束
        }
        return ans;  // 返回最大坡宽
    }
};