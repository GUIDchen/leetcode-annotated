// 题目：2352. 相等行列对（Equal Row and Column Pairs）
// 思路：枚举所有 (行 i, 列 j) 组合，内层循环逐元素比较第 i 行与第 j 列，完全相同就把计数加一。
// 时间复杂度：O(n^3)，三层循环；空间复杂度：O(1)，只用常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int equalPairs(vector<vector<int>>& grid) {  // grid：n × n 的整数矩阵
        int n = grid.size();  // 矩阵的边长
        int ans = 0;  // 相等行列对的计数
        for (int i = 0; i < n; ++i) {  // 枚举行下标 i
            for (int j = 0; j < n; ++j) {  // 枚举列下标 j
                int ok = 1;  // 先假设第 i 行与第 j 列完全相等
                for (int k = 0; k < n; ++k) {  // 逐个位置做比较
                    if (grid[i][k] != grid[k][j]) {  // 行的第 k 个元素与列的第 k 个元素不相等
                        ok = 0;  // 标记为不相等
                        break;  // 已经不可能相等，提前结束比较
                    }
                }
                ans += ok;  // ok 为 1 时这一对计入答案，为 0 时不影响结果
            }
        }
        return ans;  // 返回相等行列对的总数
    }
};