// 题目：221. 最大正方形（Maximal Square）
// 核心思路：dp[i+1][j+1] 表示以 (i,j) 为右下角的最大全 '1' 正方形边长，等于左、上、左上三个值的最小值加一。
// 时间复杂度：O(mn)，每个格子算一次；空间复杂度：O(mn)，dp 表多开一圈边界。
class Solution {  // LeetCode 约定的题解类
public:  // 对外接口
    int maximalSquare(vector<vector<char>>& matrix) {  // 求全为 '1' 的最大正方形面积
        int m = matrix.size(), n = matrix[0].size();  // 行数 m 与列数 n
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));  // dp[i+1][j+1] 是以 (i,j) 为右下角的最大正方形边长；多开一圈 0 作为边界哨兵
        int mx = 0;  // mx 记录出现过的最大边长
        for (int i = 0; i < m; ++i) {  // 逐行扫描
            for (int j = 0; j < n; ++j) {  // 逐列扫描
                if (matrix[i][j] == '1') {  // 只有当前位置是 '1' 才可能扩展出正方形
                    dp[i + 1][j + 1] = min(min(dp[i][j + 1], dp[i + 1][j]), dp[i][j]) + 1;  // 左、上、左上三个方向的最小边长加一，就是当前格的最大边长
                    mx = max(mx, dp[i + 1][j + 1]);  // 更新全局最大边长
                }  // if 结束
            }  // 内层循环结束
        }  // 外层循环结束
        return mx * mx;  // 题目要求面积，返回最大边长的平方
    }  // 方法结束
};  // 类定义结束