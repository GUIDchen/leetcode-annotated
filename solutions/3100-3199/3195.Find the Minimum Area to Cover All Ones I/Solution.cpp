// 题目：3195. 包含所有 1 的最小矩形面积 I（Find the Minimum Area to Cover All Ones I）
// 思路：把所有 1 的行、列范围分别收紧成上下左右四条边界，外接矩形就是能包含全部 1 的最小矩形，其面积即答案。
// 时间复杂度：O(m·n)，需要遍历整个矩阵；空间复杂度：O(1)，只维护四个边界变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumArea(vector<vector<int>>& grid) {  // grid：只含 0/1 的矩阵，返回包含所有 1 的最小矩形面积
        int m = grid.size(), n = grid[0].size();  // m 为行数，n 为列数
        int x1 = m, y1 = n;  // 上边界与左边界，先初始化为不可能达到的越界值
        int x2 = 0, y2 = 0;  // 下边界与右边界，先初始化为最小可能值
        for (int i = 0; i < m; ++i) {  // 逐行扫描
            for (int j = 0; j < n; ++j) {  // 逐列扫描
                if (grid[i][j] == 1) {  // 只有值为 1 的格子才参与边界更新
                    x1 = min(x1, i);  // 上边界取更小的行号
                    y1 = min(y1, j);  // 左边界取更小的列号
                    x2 = max(x2, i);  // 下边界取更大的行号
                    y2 = max(y2, j);  // 右边界取更大的列号
                }
            }
        }
        return (x2 - x1 + 1) * (y2 - y1 + 1);  // 边界长度要加 1（闭区间），相乘得到最小矩形面积
    }
};