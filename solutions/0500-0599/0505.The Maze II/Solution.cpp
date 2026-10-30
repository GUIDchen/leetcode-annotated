// 题目：505. 迷宫 II（The Maze II）
// 思路：BFS 求最短路。球一旦朝某方向滚动就会一直滚到撞墙，故每次从队首格子枚举四个方向、滚到底，距离更短才更新并入队。
// 时间复杂度：O(m*n*(m+n))，每个格子可能被松弛多次、每次滚动最多 O(m+n) 步；空间复杂度：O(m*n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {  // maze：0 为空地、1 为墙；start/destination：起点与终点坐标
        int m = maze.size(), n = maze[0].size();  // 行数 m、列数 n
        int dist[m][n];  // dist[i][j]：从起点滚到 (i, j) 的最少移动步数
        memset(dist, 0x3f, sizeof(dist));  // 按字节置 0x3f，使每个 int 变成 0x3f3f3f3f，充当无穷大
        int si = start[0], sj = start[1];  // 起点的行、列下标
        int di = destination[0], dj = destination[1];  // 终点的行、列下标
        dist[si][sj] = 0;  // 起点到自己的距离为 0
        queue<pair<int, int>> q;  // BFS 队列，存放距离被更新、待继续松弛的格子
        q.emplace(si, sj);  // 起点入队
        int dirs[5] = {-1, 0, 1, 0, -1};  // 方向增量：上、右、下、左的 (行增量, 列增量) 成对取用
        while (!q.empty()) {  // 队列非空就继续 BFS
            auto [i, j] = q.front();  // 取队首格子坐标（C++17 结构化绑定）
            q.pop();  // 弹出队首
            for (int d = 0; d < 4; ++d) {  // 枚举四个滚动方向
                int x = i, y = j, k = dist[i][j];  // 从 (i, j) 出发，k 记录滚动过程中的累计步数
                int a = dirs[d], b = dirs[d + 1];  // 当前方向的行增量 a 与列增量 b
                while (x + a >= 0 && x + a < m && y + b >= 0 && y + b < n && maze[x + a][y + b] == 0) {  // 下一格在界内且不是墙，就继续朝同一方向滚
                    x += a;  // 行坐标前进一格
                    y += b;  // 列坐标前进一格
                    ++k;  // 步数加一
                }  // 循环退出：撞墙或出界，球停在这里
                if (k < dist[x][y]) {  // 只有新路径更短才更新（滚动步数即边权，用 BFS 松弛求最短路）
                    dist[x][y] = k;  // 更新该格子的最短距离
                    q.emplace(x, y);  // 距离变小，入队继续松弛
                }  // 否则这条路径不优，直接放弃
            }  // 四个方向处理完毕
        }  // BFS 结束
        return dist[di][dj] == 0x3f3f3f3f ? -1 : dist[di][dj];  // 终点仍为无穷大说明不可达，返回 -1；否则返回最短步数
    }  // 方法结束
};  // 类定义结束