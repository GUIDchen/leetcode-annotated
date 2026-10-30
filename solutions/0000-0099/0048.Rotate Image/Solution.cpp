// 题目：48. 旋转图像（Rotate Image）
// 核心思路：顺时针旋转 90 度等于先沿水平中线上下翻转，再沿主对角线转置，两次原地交换即可，无需额外矩阵。
// 时间复杂度：O(n²)，要处理所有元素；空间复杂度：O(1)，原地交换。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    void rotate(vector<vector<int>>& matrix) {  // matrix 是 n×n 方阵，要求原地顺时针旋转 90 度，无返回值
        int n = matrix.size();  // 方阵的边长
        for (int i = 0; i < n >> 1; ++i) {  // 只处理上半部分的行就够：n >> 1 即 n/2，中间行不用动
            for (int j = 0; j < n; ++j) {  // 逐列遍历这一整行
                swap(matrix[i][j], matrix[n - i - 1][j]);  // 第 i 行与上下对称的第 n-i-1 行整行交换，完成上下翻转
            }
        }
        for (int i = 0; i < n; ++i) {  // 接着沿主对角线做转置
            for (int j = 0; j < i; ++j) {  // 只遍历下三角（j < i），避免把已经交换过的元素又换回去
                swap(matrix[i][j], matrix[j][i]);  // 交换 (i,j) 与 (j,i)，完成沿主对角线转置
            }
        }
    }
};
