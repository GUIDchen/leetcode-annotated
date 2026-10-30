// 题目：85. 最大矩形（Maximal Rectangle）
// 思路：逐行把矩阵压成一维「柱状图」——遇到 '1' 高度加一、遇到 '0' 高度清零，再对每行调用 84 题的单调栈求最大矩形。
// 时间复杂度：O(m * n)，每行做一次 O(n) 的单调栈；空间复杂度：O(n)，只额外保存高度数组与栈。

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximalRectangle(vector<vector<char>>& matrix) {  // matrix：只含 '0'/'1' 的字符矩阵
        int n = matrix[0].size();  // 列数，用第一行的长度得到
        vector<int> heights(n);  // heights[j]：以当前行为底时，第 j 列向上连续 '1' 的数量
        int ans = 0;  // 记录全矩阵中的最大矩形面积
        for (auto& row : matrix) {  // 从上到下逐行扫描，把每一行都当作柱状图的底
            for (int j = 0; j < n; ++j) {  // 逐列更新高度
                if (row[j] == '1')  // 当前格是 '1'
                    ++heights[j];  // 该列连续 '1' 的高度加一
                else  // 当前格是 '0'
                    heights[j] = 0;  // 连续段被打断，高度清零
            }
            ans = max(ans, largestRectangleArea(heights));  // 用这一行的柱状图更新答案
        }
        return ans;  // 返回最大的矩形面积
    }

    int largestRectangleArea(vector<int>& heights) {  // 复用 84 题：单调栈求柱状图中的最大矩形
        int res = 0, n = heights.size();  // res 记录最大面积；n 是柱子数量
        stack<int> stk;  // 单调栈，存下标，栈内对应高度递增
        vector<int> left(n, -1);  // left[i]：i 左边第一个更矮柱子的下标，-1 表示没有
        vector<int> right(n, n);  // right[i]：i 右边第一个更矮柱子的下标，n 表示没有
        for (int i = 0; i < n; ++i) {  // 从左往右扫描
            while (!stk.empty() && heights[stk.top()] >= heights[i]) {  // 栈顶不低于当前柱高，它的右边界就是 i
                right[stk.top()] = i;  // 记下栈顶的右边界
                stk.pop();  // 右边界已确定，弹出
            }
            if (!stk.empty()) left[i] = stk.top();  // 栈顶即 i 左边第一个更矮的柱子
            stk.push(i);  // 当前下标入栈
        }
        for (int i = 0; i < n; ++i)  // 枚举每根柱子作为矩形的高
            res = max(res, heights[i] * (right[i] - left[i] - 1));  // 宽度 = 右边界 - 左边界 - 1
        return res;  // 返回最大面积
    }
};