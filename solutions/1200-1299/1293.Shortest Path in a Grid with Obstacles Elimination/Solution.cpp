// 题目：1293. 网格中的最短路径（Shortest Path in a Grid with Obstacles Elimination）
// 核心思路：以「(行, 列, 剩余消除次数)」为状态做逐层 BFS 求最短路；先剪掉 k ≥ m+n-3 时必然可直达的情形。
// 时间复杂度：O(m·n·k)，状态数最多 m·n·(k+1)；空间复杂度：O(m·n·k)，访问标记数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int shortestPath(vector<vector<int>>& grid, int k) {  // grid 是 0/1 网格，k 是最多可消除的障碍数，返回左上到右下的最短步数
        int m = grid.size(), n = grid[0].size();  // m、n 分别是网格的行数与列数
        if (k >= m + n - 3) return m + n - 2;  // 剪枝：可消除的障碍数足够多时，最短路径上的障碍都能清掉，直接返回最短步数
        queue<vector<int>> q;  // 队列里放状态 {行, 列, 剩余消除次数}
        q.push({0, 0, k});  // 起点入队，初始剩余消除次数为 k
        vector<vector<vector<bool>>> vis(m, vector<vector<bool>>(n, vector<bool>(k + 1)));  // vis[i][j][r] 表示「到达 (i,j) 且还剩 r 次消除机会」这个状态是否已被访问
        vis[0][0][k] = true;  // 标记起点状态已访问，防止回头重复入队
        int ans = 0;  // ans 记录 BFS 的层数，也就是已走的步数
        vector<int> dirs = {-1, 0, 1, 0, -1};  // 方向数组：相邻两项组成一个方向 (dx, dy)，覆盖上下左右四个方向
        while (!q.empty()) {  // 按层 BFS，队列非空就继续
            ++ans;  // 进入新的一层，步数加一
            for (int i = q.size(); i > 0; --i) {  // 只弹出当前层的 size 个状态，保证层序不乱
                auto p = q.front();  // 取出队首状态 {行, 列, 剩余消除次数}
                k = p[2];  // 取出该状态剩余的消除次数，覆盖外层变量 k
                q.pop();  // 队首出队
                for (int j = 0; j < 4; ++j) {  // 枚举四个方向
                    int x = p[0] + dirs[j], y = p[1] + dirs[j + 1];  // 计算相邻格子的坐标
                    if (x >= 0 && x < m && y >= 0 && y < n) {  // 判断新坐标是否落在网格内部
                        if (x == m - 1 && y == n - 1) return ans;  // 走到终点，当前层数就是最短步数，直接返回
                        if (grid[x][y] == 0 && !vis[x][y][k]) {  // 空地且该状态未访问过，可以零代价通过
                            q.push({x, y, k});  // 把新状态入队
                            vis[x][y][k] = true;  // 标记新状态已访问
                        } else if (grid[x][y] == 1 && k > 0 && !vis[x][y][k - 1]) {  // 是障碍物、还有消除次数、且新状态未访问过
                            q.push({x, y, k - 1});  // 入队时消除次数减一
                            vis[x][y][k - 1] = true;  // 标记新状态已访问
                        }  // 结束 if-else 分支
                    }  // 结束边界判断
                }  // 结束方向循环
            }  // 结束当前层遍历
        }  // 结束 BFS
        return -1;  // 队列空了还没到终点，说明无法到达
    }  // 结束函数
};  // 结束题解类