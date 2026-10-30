// 题目：200. 岛屿数量（Number of Islands）
// 思路：扫描网格，遇到 '1' 就做一次 DFS 把与之连通的整块陆地改成 '0'（原地染色），计数加一。
// 时间复杂度：O(mn)，每个格子最多被访问一次；空间复杂度：O(mn)，最坏情况递归栈深度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numIslands(vector<vector<char>>& grid) {  // grid：由 '1'（陆地）和 '0'（海水）组成的二维网格，返回岛屿个数
        int m = grid.size();  // 行数
        int n = grid[0].size();  // 列数（题目保证网格至少有一行一列）
        int ans = 0;  // 岛屿计数器
        int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：相邻两项（dirs[k], dirs[k+1]）正好是上、右、下、左四个方向的增量
        auto dfs = [&](this auto&& dfs, int i, int j) -> void {  // C++23 显式对象参数 lambda：把自身传入以便递归；作用是把 (i, j) 所在的整块陆地淹没
            grid[i][j] = '0';  // 进入时先把当前格子置为 '0'，既完成染色又充当访问标记，避免重复访问或死循环
            for (int k = 0; k < 4; ++k) {  // 依次尝试四个方向
                int x = i + dirs[k], y = j + dirs[k + 1];  // 计算相邻格子的坐标
                if (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size() && grid[x][y] == '1') {  // 越界判断 + 目标格子必须是未被访问过的陆地
                    dfs(x, y);  // 继续向深处递归，把连通块一次性清空
                }
            }
        };
        for (int i = 0; i < m; ++i) {  // 逐行扫描
            for (int j = 0; j < n; ++j) {  // 逐列扫描
                if (grid[i][j] == '1') {  // 发现一块还没被淹掉的陆地，说明这是一座新岛屿
                    dfs(i, j);  // 用 DFS 把这整座岛变成海水，防止后面重复计数
                    ++ans;  // 岛屿数量加一
                }
            }
        }
        return ans;  // 返回岛屿总数
    }
};
