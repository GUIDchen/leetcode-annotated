// 题目：1905. 统计子岛屿（Count Sub Islands）
// 思路：对 grid2 做 DFS 找连通块，同时检查块内每个格子是否在 grid1 中也是陆地；若是则这整块是子岛屿。访问过的格子原地置 0 省掉 visited 数组。
// 时间复杂度：O(m·n)，每个格子最多被访问一次；空间复杂度：O(m·n)，递归栈最坏情况深度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {  // grid1：原图；grid2：待判定的图
        int m = grid1.size(), n = grid1[0].size();  // 矩阵的行数与列数
        int ans = 0;  // 统计子岛屿的个数
        int dirs[5] = {-1, 0, 1, 0, -1};  // 四方向偏移数组，长度 5 便于用 dirs[k] 和 dirs[k+1] 一次取出行列增量
        function<int(int, int)> dfs = [&](int i, int j) {  // 递归函数：从 (i, j) 出发标记整块陆地，并判断它是否完全落在 grid1 的陆地中
            int ok = grid1[i][j];  // 先看当前位置在 grid1 中是否也是陆地（是 1 否 0）
            grid2[i][j] = 0;  // 把已访问过的格子置 0，用网格本身充当 visited 标记
            for (int k = 0; k < 4; ++k) {  // 枚举四个方向
                int x = i + dirs[k], y = j + dirs[k + 1];  // 邻居的行列坐标
                if (x >= 0 && x < m && y >= 0 && y < n && grid2[x][y]) {  // 邻居在界内且是尚未访问的陆地时才继续深入
                    ok &= dfs(x, y);  // 只要有一个格子不在 grid1 的陆地中，整块岛屿就不是子岛屿
                }  // 结束 if 分支
            }  // 结束方向循环
            return ok;  // 返回 1 表示整块都在 grid1 中，返回 0 表示不是子岛屿
        };  // lambda 结束
        for (int i = 0; i < m; ++i) {  // 逐行扫描
            for (int j = 0; j < n; ++j) {  // 逐列扫描
                if (grid2[i][j]) {  // 遇到未被访问的陆地，说明发现一座新岛屿
                    ans += dfs(i, j);  // 只有整块都是子岛屿时才计入答案
                }  // 结束 if 分支
            }  // 结束列循环
        }  // 结束行循环
        return ans;  // 返回子岛屿数量
    }  // 结束题解方法
};  // 结束题解类
