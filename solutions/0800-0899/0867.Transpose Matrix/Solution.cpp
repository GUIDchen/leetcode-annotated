// 题目：867. 转置矩阵（Transpose Matrix）
// 思路：转置就是行列互换，按「n 行 m 列」新建答案矩阵，逐个把 matrix[j][i] 填到 ans[i][j]。
// 时间复杂度：O(mn)，每个元素搬一次；空间复杂度：O(mn)，需要新矩阵存放结果。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {  // matrix 是原矩阵，返回它的转置矩阵
        int m = matrix.size(), n = matrix[0].size();  // m 是原矩阵行数，n 是列数；转置后变成 n 行 m 列
        vector<vector<int>> ans(n, vector<int>(m));  // 按「n 行 m 列」一次性分配答案矩阵，避免逐个 push_back
        for (int i = 0; i < n; ++i) {  // 枚举答案矩阵的每一行 i，它对应原矩阵的第 i 列
            for (int j = 0; j < m; ++j) {  // 枚举答案矩阵的每一列 j，它对应原矩阵的第 j 行
                ans[i][j] = matrix[j][i];  // 行列互换：原矩阵的 (j, i) 元素搬到答案的 (i, j)
            }
        }
        return ans;  // 返回转置后的矩阵
    }
};  // 题解类定义结束
