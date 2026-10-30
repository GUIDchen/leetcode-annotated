// 题目：63. 不同路径 II（Unique Paths II）
// 思路：记忆化搜索，dfs(i,j) 返回从 (i,j) 走到右下角的路径数；遇障碍或越界返回 0，结果用 f 缓存避免重复计算。
// 时间复杂度：O(m*n)，每个状态只真正求解一次；空间复杂度：O(m*n)，记忆化表 f 与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {  // obstacleGrid：1 表示障碍物，0 表示空地
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();  // 记下行数和列数，供递归中判断边界
        vector<vector<int>> f(m, vector<int>(n, -1));  // 记忆化表：-1 表示该状态还没算过，非负数是已算出的答案
        auto dfs = [&](this auto&& dfs, int i, int j) {  // 递归 lambda：C++23 显式对象形参，把自身作为第一个参数以便自我调用；[&] 按引用捕获外部变量
            if (i >= m || j >= n || obstacleGrid[i][j]) {  // 越界（只能向右向下，所以不用判负）或踩到障碍物
                return 0;  // 此路不通，贡献 0 条路径
            }
            if (i == m - 1 && j == n - 1) {  // 恰好走到右下角，说明找到一条完整路径
                return 1;  // 这条路径计 1 种
            }
            if (f[i][j] == -1) {  // 该状态尚未求解过才需要递归计算
                f[i][j] = dfs(i + 1, j) + dfs(i, j + 1);  // 两种走法（向下、向右）的方案数相加，并写入缓存
            }
            return f[i][j];  // 返回缓存中的结果，避免重复搜索
        };
        return dfs(0, 0);  // 从左上角开始统计到右下角的路径数
    }
};
