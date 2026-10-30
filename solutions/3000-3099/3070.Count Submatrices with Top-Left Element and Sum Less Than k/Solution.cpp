// 题目：3070. 元素和小于等于 k 的子矩阵的数目（Count Submatrices with Top-Left Element and Sum Less Than k）
// 核心思路：因为所有子矩阵都必须以 (0,0) 为左上角，所以候选只有「左上角固定、右下角任选」的 n·m 个；用二维前缀和递推即可 O(1) 算出每个候选的和并计数。
// 时间复杂度：O(m·n)，每个格子递推一次；空间复杂度：O(m·n)，前缀和表比原矩阵多一行一列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countSubmatrices(vector<vector<int>>& grid, int k) {  // grid：非负整数矩阵；k：元素和上界；返回元素和小于等于 k 的、以左上角开头的子矩阵个数
        int m = grid.size(), n = grid[0].size();  // m 行数、n 列数，用于确定前缀和表的规模与循环边界
        int s[m + 1][n + 1];  // 二维前缀和，多开一行一列（下标从 1 开始），s[i][j] 表示左上角 i×j 子矩阵的元素和
        memset(s, 0, sizeof(s));  // 把前缀和表整体清零，保证第 0 行、第 0 列是 0 边界
        int ans = 0;  // 计数器：满足 s[i][j] <= k 的候选子矩阵个数
        for (int i = 1; i <= m; ++i) {  // 按行递推前缀和，i 从 1 开始以对齐多开的一行
            for (int j = 1; j <= n; ++j) {  // 按列递推前缀和，j 从 1 开始以对齐多开的一列
                s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + grid[i - 1][j - 1];  // 容斥公式：上方 + 左方 - 左上方 + 当前格，得到左上角 i×j 子矩阵的和
                if (s[i][j] <= k) {  // 所有候选子矩阵都以 (0,0) 为左上角，和不超过 k 就计入答案
                    ++ans;  // 答案计数加一
                }
            }
        }
        return ans;  // 返回满足条件的子矩阵数目
    }
};