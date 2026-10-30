// 题目：73. 矩阵置零（Set Matrix Zeroes）
// 思路：两趟扫描——第一趟记录哪些行、哪些列含有 0；第二趟把「所在行或所在列被标记」的元素统一置 0，这样不会因为边改边查而污染判断。
// 时间复杂度：O(m·n)，矩阵只被完整扫描两遍；空间复杂度：O(m + n)，额外用两个标记数组记录行与列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    void setZeroes(vector<vector<int>>& matrix) {  // matrix：待处理的二维矩阵，原地修改，无返回值
        int m = matrix.size(), n = matrix[0].size();  // m 为行数，n 为列数（题目保证矩阵非空）
        vector<bool> row(m);  // row[i] 表示第 i 行出现了 0，需要整行清零
        vector<bool> col(n);  // col[j] 表示第 j 列出现了 0，需要整列清零
        for (int i = 0; i < m; ++i) {  // 第一趟：扫描整个矩阵做标记
            for (int j = 0; j < n; ++j) {  // 遍历当前行的每一列
                if (matrix[i][j] == 0) {  // 发现一个原生的 0
                    row[i] = col[j] = true;  // 把它的行与列都标记为需要清零
                }
            }
        }
        for (int i = 0; i < m; ++i) {  // 第二趟：依据标记执行清零
            for (int j = 0; j < n; ++j) {  // 遍历当前行的每一列
                if (row[i] || col[j]) {  // 只要该元素所在行或所在列被标记过
                    matrix[i][j] = 0;  // 就把它置 0
                }
            }
        }
    }
};
