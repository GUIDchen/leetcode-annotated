// 题目：1254. 统计封闭岛屿的数目（Number of Closed Islands）
// 思路：从每个尚未访问的陆地格出发做 DFS，把整座岛淹掉（置 1）；DFS 途中若碰到矩阵边界就说明这座岛不封闭，用按位与把该岛的答案置 0。
// 时间复杂度：O(mn)，每个格子最多被访问一次；空间复杂度：O(mn)，递归栈最坏深度为格子总数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int closedIsland(vector<vector<int>>& grid) {  // grid：0 表示陆地、1 表示水；返回四周都被水包围的岛屿个数
        int m = grid.size(), n = grid[0].size();  // m 为行数，n 为列数（题目保证至少一行一列）
        int ans = 0;  // ans 累计封闭岛屿的个数
        int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：相邻两项组成一个方向 (dr, dc) = (-1,0) (0,1) (1,0) (0,-1)，即上下右左
        function<int(int, int)> dfs = [&](int i, int j) -> int {  // 用 std::function 写递归 lambda，便于在函数体内调用自身
            int res = i > 0 && i < m - 1 && j > 0 && j < n - 1 ? 1 : 0;  // 若当前格不在最外圈则记为 1（仍可能封闭），在边界上则直接判 0（不封闭）
            grid[i][j] = 1;  // 先把当前格改写成水，相当于标记已访问，防止重复搜索与死循环
            for (int k = 0; k < 4; ++k) {  // 依次尝试四个方向
                int x = i + dirs[k], y = j + dirs[k + 1];  // 由方向数组取出相邻格坐标（dirs[k] 是行偏移，dirs[k+1] 是列偏移）
                if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 0) {  // 相邻格在界内且仍是陆地时继续深搜
                    res &= dfs(x, y);  // 按位与保证：只要有一座相邻子岛不封闭，整座岛就不封闭
                }
            }
            return res;  // 返回整座岛是否封闭（1 表示封闭，0 表示不封闭）
        };
        for (int i = 0; i < m; ++i) {  // 逐行扫描每个格子
            for (int j = 0; j < n; ++j) {  // 逐列扫描每个格子
                ans += grid[i][j] == 0 && dfs(i, j);  // 只从未被访问的陆地出发搜索，DFS 返回真则计数加一
            }
        }
        return ans;  // 返回封闭岛屿总数
    }
};