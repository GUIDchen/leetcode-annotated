// 题目：84. 柱状图中最大的矩形（Largest Rectangle in Histogram）
// 思路：单调递增栈一次遍历求出每根柱子左边、右边第一个更矮的位置，再以每根柱子为高，用「右边界 - 左边界 - 1」作宽算面积。
// 时间复杂度：O(n)，每根柱子最多入栈、出栈各一次；空间复杂度：O(n)，栈与 left/right 数组。

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int largestRectangleArea(vector<int>& heights) {  // heights：每根柱子的高度
        int res = 0, n = heights.size();  // res 记录最大矩形面积；n 是柱子总数
        stack<int> stk;  // 单调栈，存下标，栈内下标对应的高度从栈底到栈顶严格递增
        vector<int> left(n, -1);  // left[i]：i 左边第一个比 heights[i] 矮的下标；-1 表示左边没有更矮的
        vector<int> right(n, n);  // right[i]：i 右边第一个比 heights[i] 矮的下标；n 表示右边没有更矮的
        for (int i = 0; i < n; ++i) {  // 从左往右扫描，一次遍历同时确定右边界和左边界
            while (!stk.empty() && heights[stk.top()] >= heights[i]) {  // 栈顶不低于当前柱，说明栈顶的右边界正是 i
                right[stk.top()] = i;  // 记下栈顶柱子的右侧第一个更矮位置
                stk.pop();  // 栈顶的右边界已经确定，弹出
            }
            if (!stk.empty()) left[i] = stk.top();  // 弹出所有不低于 i 的柱子后，栈顶就是 i 左边第一个更矮的柱子
            stk.push(i);  // 当前下标入栈，继续维持栈内高度递增
        }
        for (int i = 0; i < n; ++i)  // 枚举每根柱子作为矩形的“高”
            res = max(res, heights[i] * (right[i] - left[i] - 1));  // 宽 = 右边界 - 左边界 - 1，乘高度更新答案
        return res;  // 返回最大面积
    }
};