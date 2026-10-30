// 题目：2482. 行和列中一和零的差值（Difference Between Ones and Zeros in Row and Column）
// 思路：先统计每行、每列的 1 的个数，再对每个格子用 ones(i)+ones(j)-zeros(i)-zeros(j) 计算差值，其中 zeros 由长度减 ones 得到。
// 时间复杂度：O(m·n)，两遍扫描矩阵；空间复杂度：O(m·n)，结果矩阵之外还有 O(m+n) 的行列计数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> onesMinusZeros(vector<vector<int>>& grid) {  // grid：m×n 的 0/1 矩阵；返回同尺寸的差值矩阵
        int m = grid.size(), n = grid[0].size();  // 行数 m 与列数 n
        vector<int> rows(m);  // rows[i]：第 i 行 1 的个数
        vector<int> cols(n);  // cols[j]：第 j 列 1 的个数
        for (int i = 0; i < m; ++i) {  // 遍历所有行
            for (int j = 0; j < n; ++j) {  // 遍历所有列
                int v = grid[i][j];  // 取出当前格子的值（0 或 1）
                rows[i] += v;  // 是 1 就累加进行计数，是 0 则加 0 无影响
                cols[j] += v;  // 同时累加进列计数
            }  // 结束列循环
        }  // 结束行循环，统计完成
        vector<vector<int>> diff(m, vector<int>(n));  // 结果矩阵，m×n，默认全部初始化为 0
        for (int i = 0; i < m; ++i) {  // 逐行填结果
            for (int j = 0; j < n; ++j) {  // 逐列填结果
                diff[i][j] = rows[i] + cols[j] - (n - rows[i]) - (m - cols[j]);  // 行、列的 1 的个数减去各自 0 的个数（zeros = 长度 - ones）
            }  // 结束列循环
        }  // 结束行循环
        return diff;  // 返回差值矩阵
    }  // 结束题解方法
};  // 结束题解类