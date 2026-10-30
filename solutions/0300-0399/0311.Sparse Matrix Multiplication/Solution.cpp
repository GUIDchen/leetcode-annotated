// 题目：311. 稀疏矩阵的乘法（Sparse Matrix Multiplication）
// 思路：按矩阵乘法定义三重循环直接累加，0 元素乘积为 0 不影响结果，因此不需要额外利用稀疏性。
// 时间复杂度：O(m·n·k)，m、n 为结果行列数，k 为公共维；空间复杂度：O(m·n)，只额外占用结果矩阵。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {  // mat1：m×k 矩阵；mat2：k×n 矩阵；返回 m×n 的乘积
        int m = mat1.size(), n = mat2[0].size();  // m：结果行数（mat1 的行数）；n：结果列数（mat2 的列数）
        vector<vector<int>> ans(m, vector<int>(n));  // 结果矩阵，值初始化保证每个元素从 0 开始累加
        for (int i = 0; i < m; ++i) {  // 枚举结果的每一行
            for (int j = 0; j < n; ++j) {  // 枚举结果的每一列
                for (int k = 0; k < mat2.size(); ++k) {  // 枚举公共维 k，即 mat1 的列数（等于 mat2 的行数）
                    ans[i][j] += mat1[i][k] * mat2[k][j];  // 累加「第 i 行第 k 列」与「第 k 行第 j 列」的乘积
                }
            }
        }
        return ans;  // 返回乘积矩阵
    }
};