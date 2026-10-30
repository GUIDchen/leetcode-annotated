// 题目：566. 重塑矩阵（Reshape the Matrix）
// 思路：元素总数不同则原样返回；否则按行优先的一维下标 i 直接映射：新矩阵 (i/c, i%c) 取原矩阵 (i/n, i%n) 的元素。
// 时间复杂度：O(m·n)，每个元素搬运一次；空间复杂度：O(r·c)，新建结果矩阵。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {  // mat 是原矩阵，r、c 是新行列数，返回重塑后的矩阵
        int m = mat.size(), n = mat[0].size();  // m、n 是原矩阵的行数与列数
        if (m * n != r * c) {  // 元素总数不等时无法重塑，按题意返回原矩阵
            return mat;  // 原样返回原矩阵
        }  // 不匹配分支结束
        vector<vector<int>> ans(r, vector<int>(c));  // 先建好 r 行 c 列的空矩阵作为结果容器
        for (int i = 0; i < m * n; ++i) {  // 按行优先的一维下标遍历全部元素
            ans[i / c][i % c] = mat[i / n][i % n];  // i 映射到新矩阵 (i/c, i%c) 与原矩阵 (i/n, i%n)，逐元素搬运
        }  // 搬运循环结束
        return ans;  // 返回重塑后的矩阵
    }
};