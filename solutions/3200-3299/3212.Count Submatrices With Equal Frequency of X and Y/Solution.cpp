// 题目：3212. 统计 X 和 Y 频数相等的子矩阵数量（Count Submatrices With Equal Frequency of X and Y）
// 思路：题目统计的是以 (0,0) 为左上角的子矩阵，用二维前缀和分别数出其中 X 与 Y 的个数，X 个数为正且等于 Y 个数时答案加一。
// 时间复杂度：O(mn)，每个格子常数次运算；空间复杂度：O(mn)，存放两通道前缀和。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfSubmatrices(vector<vector<char>>& grid) {  // grid：只含 'X'、'Y'、'.' 的字符矩阵
        int m = grid.size(), n = grid[0].size();  // m 行 n 列
        vector<vector<vector<int>>> s(m + 1, vector<vector<int>>(n + 1, vector<int>(2)));  // 三维前缀和：s[i][j][0] / s[i][j][1] 分别是左上角到 (i,j) 区域内的 X / Y 个数
        int ans = 0;  // 满足条件的子矩阵计数
        for (int i = 1; i <= m; ++i) {  // 前缀和下标从 1 开始，方便用 i-1 处理边界
            for (int j = 1; j <= n; ++j) {  // 逐列递推每个位置的前缀和
                s[i][j][0] = s[i - 1][j][0] + s[i][j - 1][0] - s[i - 1][j - 1][0]  // 二维前缀和容斥：上 + 左 - 左上，再加上本格
                    + (grid[i - 1][j - 1] == 'X' ? 1 : 0);  // 本格是 X 时贡献 1，否则贡献 0
                s[i][j][1] = s[i - 1][j][1] + s[i][j - 1][1] - s[i - 1][j - 1][1]  // 同理统计 Y 的前缀和：上 + 左 - 左上
                    + (grid[i - 1][j - 1] == 'Y' ? 1 : 0);  // 本格是 Y 时贡献 1，否则贡献 0
                if (s[i][j][0] > 0 && s[i][j][0] == s[i][j][1]) {  // 以 (0,0) 为左上角、X 个数为正且与 Y 个数相等
                    ++ans;  // 该子矩阵符合条件，答案加一
                }
            }
        }
        return ans;  // 返回满足条件的子矩阵数量
    }
};