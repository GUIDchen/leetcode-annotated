// 题目：1572. 矩阵对角线元素的和（Matrix Diagonal Sum）
// 思路：一次遍历每一行，累加主对角线 mat[i][i] 与副对角线 mat[i][n-1-i]；中心格子重合时用三元表达式补 0，避免重复计算。
// 时间复杂度：O(n)，n 为矩阵阶数，只遍历 n 行；空间复杂度：O(1)，只用常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int diagonalSum(vector<vector<int>>& mat) {  // mat：n×n 的二维矩阵
        int ans = 0;  // 累加两条对角线元素之和
        int n = mat.size();  // 矩阵的阶数
        for (int i = 0; i < n; ++i) {  // 逐行处理，i 同时是主对角线的列下标
            int j = n - i - 1;  // 副对角线在第 i 行上的列下标
            ans += mat[i][i] + (i == j ? 0 : mat[i][j]);  // 累加主对角线元素；两条对角线重合（奇数阶中心）时补 0 防止重复
        }
        return ans;  // 返回两条对角线上元素的总和
    }
};