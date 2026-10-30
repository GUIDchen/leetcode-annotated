// 4052. 行列循环移位（Cyclically Shift Rows and Columns）
// 核心思路：先用中间矩阵完成每一行的循环移位，再在列方向上完成每一列的循环移位
// 复杂度：时间 O(n^2)，空间 O(n^2)
class Solution {  // 题解主类
public:  // 对外接口
    vector<vector<int>> cyclicShift(int n, vector<vector<int>>& grid, vector<int>& rowShift, vector<int>& colShift) {  // 按行循环移位后再按列循环移位，返回新矩阵
        vector<vector<int>> t(n, vector<int>(n));  // 中间矩阵，存放行移位后的结果
        for (int i = 0; i < n; i++) {  // 逐行处理行移位
            for (int j = 0; j < n; j++) {  // 逐列处理当前行的每个元素
                t[i][(j - rowShift[i] + n) % n] = grid[i][j];  // 把 (i, j) 移到第 (j - rowShift[i] + n) % n 列，加 n 取模保证下标非负
            }  // 内层循环结束
        }  // 行移位结束
        vector<vector<int>> ans(n, vector<int>(n));  // 答案矩阵
        for (int j = 0; j < n; j++) {  // 逐列处理列移位
            for (int i = 0; i < n; i++) {  // 逐行处理当前列的每个元素
                ans[(i - colShift[j] + n) % n][j] = t[i][j];  // 把 (i, j) 移到第 (i - colShift[j] + n) % n 行，实现竖直方向的循环移位
            }  // 内层循环结束
        }  // 列移位结束
        return ans;  // 返回移位后的矩阵
    }  // 方法结束
};  // 类结束
