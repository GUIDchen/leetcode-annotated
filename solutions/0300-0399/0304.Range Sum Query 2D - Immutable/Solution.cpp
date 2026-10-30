// 题目：304. 二维区域和检索 - 矩阵不可变（Range Sum Query 2D - Immutable）
// 思路：预处理二维前缀和，用容斥原理在 O(1) 时间内回答任意子矩阵的元素和。
// 时间复杂度：构造 O(mn)、每次查询 O(1)；空间复杂度：O(mn)，存 (m+1)×(n+1) 的前缀和。
class NumMatrix {  // LeetCode 约定的题解类
public:  // 对外接口
    vector<vector<int>> s;  // 二维前缀和：s[i][j] 表示左上角 (0,0) 到 (i-1,j-1) 的子矩阵元素和

    NumMatrix(vector<vector<int>>& matrix) {  // 构造函数：matrix 是输入矩阵
        int m = matrix.size(), n = matrix[0].size();  // 行数 m 与列数 n
        s.resize(m + 1, vector<int>(n + 1));  // 多开一行一列，第 0 行列作哨兵 0，省掉边界特判
        for (int i = 0; i < m; ++i) {  // 逐行递推
            for (int j = 0; j < n; ++j) {  // 逐列递推
                s[i + 1][j + 1] = s[i + 1][j] + s[i][j + 1] - s[i][j] + matrix[i][j];  // 容斥：上方 + 左方 - 被重复加的左上角 + 当前元素
            }  // 列循环结束
        }  // 行循环结束
    }  // 构造函数结束

    int sumRegion(int row1, int col1, int row2, int col2) {  // 查询左上 (row1,col1) 到右下 (row2,col2) 的子矩阵和
        return s[row2 + 1][col2 + 1] - s[row2 + 1][col1] - s[row1][col2 + 1] + s[row1][col1];  // 容斥：大矩形 - 上方 - 左方 + 被减两次的左上角，O(1)
    }  // sumRegion 结束
};  // NumMatrix 类结束

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */