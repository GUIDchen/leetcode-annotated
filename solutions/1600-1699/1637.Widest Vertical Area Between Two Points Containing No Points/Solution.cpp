// 题目：1637. 两点之间不包含任何点的最宽垂直区域（Widest Vertical Area Between Two Points Containing No Points）
// 思路：纵坐标不参与计算，把点按横坐标排序后，相邻两点横坐标差的最大值就是答案。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，只用到常数个整型变量（排序的栈空间另计）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxWidthOfVerticalArea(vector<vector<int>>& points) {  // points 是若干点坐标，返回最宽的、内部不含任何点的垂直区域宽度
        sort(points.begin(), points.end());  // 按 (x, y) 字典序排序，这样相同或相邻的横坐标会连续排列
        int ans = 0;  // 记录当前找到的最大宽度
        for (int i = 0; i < points.size() - 1; ++i) {  // 遍历相邻的两个点（到倒数第二个点为止，避免下标越界）
            ans = max(ans, points[i + 1][0] - points[i][0]);  // 用相邻两点横坐标之差更新最大值
        }  // 相邻点循环结束
        return ans;  // 返回最宽垂直区域的宽度
    }  // maxWidthOfVerticalArea 方法结束
};  // 题解类定义结束