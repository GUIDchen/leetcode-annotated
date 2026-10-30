// 题目：931. 下降路径最小和（Minimum Falling Path Sum）
// 思路：按行动态规划。f[j] 是落到上一行第 j 列的最小和，当前格取左上、正上、右上三者的最小值再加自身。
// 时间复杂度：O(n^2)，n 行 n 列各算一次；空间复杂度：O(n)，只保留上一行与当前行两个一维数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minFallingPathSum(vector<vector<int>>& matrix) {  // matrix 是 n×n 矩阵，返回从第一行落到最后一行的最小路径和
        int n = matrix.size();  // 矩阵边长
        vector<int> f(n);  // f[j]：到达上一行第 j 列的最小下降路径和；第一行上方视为 0
        for (auto& row : matrix) {  // 自上而下逐行递推
            auto g = f;  // 把上一行状态拷贝到当前行，作为三路取最小的起点
            for (int j = 0; j < n; ++j) {  // 枚举当前行的每一列
                if (j) {  // 左边界之外没有左上方格子，需要判断存在性
                    g[j] = min(g[j], f[j - 1]);
                }  // 可以从左上方转移过来
                if (j + 1 < n) {  // 右边界之外也没有右上方格子
                    g[j] = min(g[j], f[j + 1]);
                }  // 可以从右上方转移过来
                g[j] += row[j];  // 加上当前格子的值，得到到达当前格子的最小和
            }
            f = move(g);  // 当前行成为下一行的“上一行”
        }
        return *min_element(f.begin(), f.end());  // 最后一行的最小和就是答案
    }
};