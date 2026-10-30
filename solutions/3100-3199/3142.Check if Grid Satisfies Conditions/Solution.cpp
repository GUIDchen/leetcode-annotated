// 题目：3142. 判断矩阵是否满足条件（Check if Grid Satisfies Conditions）
// 思路：逐格检查两条约束——与正下方格子必须不同，与正右方格子必须不相等（即同行相邻不能相同）。
// 时间复杂度：O(m*n)，每个格子只做常数次比较；空间复杂度：O(1)，只用了行列计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool satisfiesConditions(vector<vector<int>>& grid) {  // grid：待检查的矩阵，返回是否满足条件
        int m = grid.size(), n = grid[0].size();  // m 是行数，n 是列数
        for (int i = 0; i < m; ++i) {  // 逐行遍历
            for (int j = 0; j < n; ++j) {  // 逐列遍历
                if (i + 1 < m && grid[i][j] != grid[i + 1][j]) {  // 要求同一列上下相邻的两个元素不同
                    return false;  // 相同即违反条件
                }  // 纵向检查结束
                if (j + 1 < n && grid[i][j] == grid[i][j + 1]) {  // 要求同一行左右相邻的两个元素相等
                    return false;  // 相同即违反条件
                }  // 横向检查结束
            }  // 列遍历结束
        }  // 行遍历结束
        return true;  // 所有格子都没被否决，说明满足条件
    }  // 方法结束
};  // 类定义结束