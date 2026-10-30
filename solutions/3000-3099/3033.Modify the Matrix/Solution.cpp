// 题目：3033. 修改矩阵（Modify the Matrix）
// 思路：先按列求出每一列的最大值，再把该列中所有 -1 替换成这个最大值。
// 时间复杂度：O(m * n)，每列扫两遍；空间复杂度：O(1)，原地修改，只用常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> modifiedMatrix(vector<vector<int>>& matrix) {  // matrix：待修改的矩阵，-1 为待替换的占位
        int m = matrix.size(), n = matrix[0].size();  // m：行数；n：列数
        for (int j = 0; j < n; ++j) {  // 逐列处理，因为替换值取决于同一列的最大值
            int mx = -1;  // 该列最大值，题目中元素非负，用 -1 作初值
            for (int i = 0; i < m; ++i) {  // 扫描整列求最大值
                mx = max(mx, matrix[i][j]);  // 用当前元素更新列最大值
            }
            for (int i = 0; i < m; ++i) {  // 再扫一遍该列，替换所有占位符
                if (matrix[i][j] == -1) {  // 只处理 -1 的格子
                    matrix[i][j] = mx;  // 用本列最大值填上
                }
            }
        }
        return matrix;  // 返回原地修改后的矩阵
    }
};