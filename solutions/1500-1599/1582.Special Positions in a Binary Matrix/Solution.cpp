// 题目：1582. 二进制矩阵中的特殊位置（Special Positions in a Binary Matrix）
// 思路：先统计每一行与每一列中 1 的个数，再遍历所有值为 1 的格子，若它所在行与所在列的 1 的个数都恰好为 1，则它是一个特殊位置。
// 时间复杂度：O(m * n)，矩阵被扫描两遍；空间复杂度：O(m + n)，rows 与 cols 两个计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numSpecial(vector<vector<int>>& mat) {  // mat：输入的 0/1 矩阵
        int m = mat.size(), n = mat[0].size();  // m 为行数，n 为列数
        vector<int> rows(m);  // rows[i] 记录第 i 行中 1 的个数（vector 默认初始化为 0）
        vector<int> cols(n);  // cols[j] 记录第 j 列中 1 的个数（vector 默认初始化为 0）

        for (int i = 0; i < m; ++i) {  // 逐行遍历矩阵
            for (int j = 0; j < n; ++j) {  // 逐列遍历当前行
                rows[i] += mat[i][j];  // 当前元素累加到所在行的计数
                cols[j] += mat[i][j];  // 同一元素再累加到所在列的计数
            }  // 列循环结束
        }  // 行循环结束

        int ans = 0;  // 特殊位置的个数
        for (int i = 0; i < m; ++i) {  // 再次逐行扫描
            for (int j = 0; j < n; ++j) {  // 逐列检查每个格子
                if (mat[i][j] == 1 && rows[i] == 1 && cols[j] == 1) {  // 值为 1 且所在行、列各自都只有一个 1，才是特殊位置
                    ans++;  // 计数加一
                }  // if 分支结束
            }  // 列循环结束
        }  // 行循环结束

        return ans;  // 返回特殊位置的个数
    }  // 方法结束
};  // 题解类结束
