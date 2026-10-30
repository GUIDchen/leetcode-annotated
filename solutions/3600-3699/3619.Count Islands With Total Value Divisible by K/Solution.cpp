// 3619. Count Islands With Total Value Divisible by K / 总价值可以被 K 整除的岛屿数目
// 核心思路：网格 DFS 洪水填充，每次从一块未访问的陆地出发累加整座岛的价值并把格子清零，若总和能被 k 整除就计数。
// 复杂度：时间复杂度 O(m * n)，空间复杂度 O(m * n)，m、n 分别为网格的行数与列数。
class Solution {  // 定义题解类
public:  // 公有成员：对外提供 countIslands
    int countIslands(vector<vector<int>>& grid, int k) {  // 统计总价值能被 k 整除的岛屿数量
        int m = grid.size(), n = grid[0].size();  // 行数 m、列数 n
        vector<int> dirs = {-1, 0, 1, 0, -1};  // 方向数组：相邻两项组合成上下左右四个方向

        auto dfs = [&](this auto&& dfs, int i, int j) -> long long {  // 递归 Lambda：从 (i, j) 出发淹没整座岛并返回其总价值
            long long s = grid[i][j];  // 先累加当前格子的价值
            grid[i][j] = 0;  // 把当前格子置 0，充当已访问标记
            for (int d = 0; d < 4; ++d) {  // 枚举四个方向
                int x = i + dirs[d], y = j + dirs[d + 1];  // 由方向数组算出相邻格子的坐标
                if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y]) {  // 邻格在界内且仍有价值才继续深入
                    s += dfs(x, y);  // 递归累加邻格所在整块的价值
                }  // 结束邻格判断
            }  // 结束四方向枚举
            return s;  // 返回这座岛的总价值
        };  // dfs 闭包定义结束

        int ans = 0;  // ans 记录满足条件的岛屿数量
        for (int i = 0; i < m; ++i) {  // 逐行扫描
            for (int j = 0; j < n; ++j) {  // 逐列扫描
                if (grid[i][j] && dfs(i, j) % k == 0) {  // 遇到未访问的陆地就淹没它，并判断其总价值能否被 k 整除
                    ++ans;  // 能整除则计数加一
                }  // 结束判断
            }  // 结束列扫描
        }  // 结束行扫描
        return ans;  // 返回岛屿数量
    }  // 方法结束
};  // 类定义结束
