// 题目：64. 最小路径和（Minimum Path Sum）
// 思路：二维 DP，f[i][j] 表示走到 (i,j) 的最小路径和；先铺好第一行、第一列，其余格取上方与左方的较小值再加本格的值。
// 时间复杂度：O(m*n)，每格只算一次；空间复杂度：O(m*n)，DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minPathSum(vector<vector<int>>& grid) {  // grid：非负整数矩阵，从左上走到右下，只能向右或向下
        int m = grid.size(), n = grid[0].size();  // 行数、列数
        int f[m][n];  // DP 表：f[i][j] 表示到达 (i,j) 的最小路径和（边长由运行时决定，属于题目允许的变长数组）
        f[0][0] = grid[0][0];  // 起点没有前驱，路径和就是自己的值
        for (int i = 1; i < m; ++i) {  // 初始化第一列
            f[i][0] = f[i - 1][0] + grid[i][0];  // 第一列只能从上方来，累加即可
        }
        for (int j = 1; j < n; ++j) {  // 初始化第一行
            f[0][j] = f[0][j - 1] + grid[0][j];  // 第一行只能从左方来，累加即可
        }
        for (int i = 1; i < m; ++i) {  // 其余格子从上到下逐行填
            for (int j = 1; j < n; ++j) {  // 每行从左到右填，保证依赖已算好
                f[i][j] = min(f[i - 1][j], f[i][j - 1]) + grid[i][j];  // 取上方、左方中较小的路径和，再加上本格代价
            }
        }
        return f[m - 1][n - 1];  // 右下角的最小路径和即答案
    }
};
