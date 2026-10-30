// 题目：3643. 垂直翻转子矩阵（Flip Square Submatrix Vertically）
// 核心思路：子矩阵是边长为 k 的正方形，垂直翻转即上下镜像；只需遍历上半部分的 k/2 行，把它与下方对称行在同一列上的元素逐个交换即可。
// 复杂度：时间 O(k²)，共处理约 k²/2 对元素；空间 O(1)，原地修改，不计返回值。
class Solution {  // LeetCode 题解类
public:  // 对外接口
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k) {  // grid：矩阵；x、y：子矩阵左上角；k：子矩阵边长
        for (int i = x; i < x + k / 2; i++) {  // 只枚举上半部分的 k/2 行，与下半部分对称交换
            int i2 = x + k - 1 - (i - x);  // 与第 i 行关于子矩阵水平中轴上下对称的行号
            for (int j = y; j < y + k; j++) {  // 遍历子矩阵的每一列
                swap(grid[i][j], grid[i2][j]);  // 交换上下对称位置上的两个元素
            }
        }
        return grid;  // 返回原地修改后的矩阵
    }
};
