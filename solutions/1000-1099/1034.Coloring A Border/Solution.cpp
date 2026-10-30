// 题目：1034. 边界着色（Coloring A Border）
// 思路：从 (row, col) 做 DFS 遍历同色连通块；某格若贴矩阵边界或存在异色邻居，就是该连通块的边界，把它涂成 color。
// 时间复杂度：O(m*n)，每个格子最多访问一次；空间复杂度：O(m*n)，访问标记与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {  // 把 (row, col) 所在同色连通块的「边界格」涂成 color，返回原地修改后的矩阵
        int m = grid.size();  // 行数
        int n = grid[0].size();  // 列数
        bool vis[m][n];  // 访问标记（变长数组，行列数运行时才知道）
        memset(vis, false, sizeof(vis));  // memset 按字节清零，全表置为未访问
        int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：相邻两项组成 (上、右、下、左) 的四个偏移
        function<void(int, int, int)> dfs = [&](int i, int j, int c) {  // 递归 lambda：i、j 为当前格，c 为该连通块原来的颜色
            vis[i][j] = true;  // 进入即标记已访问，避免同一格被反复递归
            for (int k = 0; k < 4; ++k) {  // 枚举四个相邻方向
                int x = i + dirs[k];  // 相邻格的行坐标
                int y = j + dirs[k + 1];  // 相邻格的列坐标
                if (x >= 0 && x < m && y >= 0 && y < n) {  // 相邻格仍在矩阵内
                    if (!vis[x][y]) {  // 相邻格还没被访问过
                        if (grid[x][y] == c) {  // 颜色相同说明属于同一个连通块
                            dfs(x, y, c);  // 继续深入搜索这块区域
                        } else {  // 颜色不同（可能是别的块，或已被改色）
                            grid[i][j] = color;  // 当前格紧邻异色块，属于边界，重新着色
                        }  // 颜色判断结束
                    }  // 访问判断结束
                } else {  // 走到矩阵外，说明当前格贴着外边框
                    grid[i][j] = color;  // 贴边的格子也是边界，重新着色
                }  // 越界判断结束
            }  // 方向枚举结束
        };  // lambda 定义结束
        dfs(row, col, grid[row][col]);  // 从起点开始深搜，原始颜色取起点格子的颜色（否则原色会被新色覆盖后判断出错）
        return grid;  // 返回原地修改后的矩阵
    }  // 方法结束
};  // 类定义结束