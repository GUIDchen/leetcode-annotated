// 题目：3286. 穿越网格图的安全路径（Find a Safe Walk Through a Grid）
// 思路：把 grid[i][j] 看成进入该格要付出的代价，用 SPFA（队列松弛）求起点到终点的最小累计代价，再判断是否严格小于 health。
// 时间复杂度：O(mn)，每个格子可能被松弛多次但常数很小；空间复杂度：O(mn)，用于 dist 表与队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool findSafeWalk(vector<vector<int>>& grid, int health) {  // grid：0/1 网格（1 表示踩上去消耗 1 点生命值）；health：初始生命值
        int m = grid.size();  // 网格行数
        int n = grid[0].size();  // 网格列数
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));  // dist[x][y]：从左上角走到 (x,y) 累计消耗的最小生命值，先全置为无穷大
        dist[0][0] = grid[0][0];  // 起点自身若为 1 也要先扣血，所以把起点代价直接设为 grid[0][0]
        queue<pair<int, int>> q;  // SPFA 队列：存放还需要去松弛邻居的格子坐标
        q.emplace(0, 0);  // 起点入队，开始最短路松弛
        int dirs[5] = {-1, 0, 1, 0, -1};  // 四方向增量，依次取相邻两项即可得到 (dx, dy)
        while (!q.empty()) {  // 队列非空说明还可能存在更短的路径
            auto [x, y] = q.front();  // C++17 结构化绑定：取出队首坐标
            q.pop();  // 弹出队首
            for (int i = 0; i < 4; ++i) {  // 枚举上下左右四个邻居
                int nx = x + dirs[i];  // 邻居的行号
                int ny = y + dirs[i + 1];  // 邻居的列号
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && dist[nx][ny] > dist[x][y] + grid[nx][ny]) {  // 先判越界，再用「当前代价 + 邻居自身代价」尝试松弛
                    dist[nx][ny] = dist[x][y] + grid[nx][ny];  // 松弛成功：更新邻居的最小累计代价
                    q.emplace(nx, ny);  // 邻居代价变小，入队以便继续向外传播
                }  // 四个方向枚举结束
            }  // while 结束：队列已空，最短路收敛
        }  // 终点累计消耗严格小于 health 才走得出去
        return dist[m - 1][n - 1] < health;  // findSafeWalk 结束
    }  // Solution 类结束
};
