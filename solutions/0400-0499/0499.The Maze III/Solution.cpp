// 题目：499. 迷宫 III（The Maze III）
// 思路：把「球停下来的位置」当作状态做 BFS，记录每个状态的最短滚动距离与字典序最小的路径；滚到洞就停，最后取距离优先、路径字典序次优的解。
// 时间复杂度：O(m*n*max(m,n))，每个状态最多向四个方向各滚一遍；空间复杂度：O(m*n)，dist 与 path 各占 O(m*n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {  // maze 中 0 是空地、1 是墙；ball 是起点坐标，hole 是洞的坐标
        int m = maze.size();  // 迷宫行数
        int n = maze[0].size();  // 迷宫列数
        int r = ball[0], c = ball[1];  // 起点的行、列下标
        int rh = hole[0], ch = hole[1];  // 洞的行、列下标
        queue<pair<int, int>> q;  // BFS 队列，元素是球的「停靠点」
        q.push({r, c});  // 起点先入队
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));  // 到每个停靠点的最短滚动距离，初始为无穷大
        dist[r][c] = 0;  // 起点到自己的距离是 0
        vector<vector<string>> path(m, vector<string>(n, ""));  // 到每个停靠点的最小字典序路径，空串表示尚未到达
        vector<vector<int>> dirs = {{-1, 0, 'u'}, {1, 0, 'd'}, {0, -1, 'l'}, {0, 1, 'r'}};  // 四个滚动方向及其字母：u 上、d 下、l 左、r 右（u<d<l<r 正好是字典序）
        while (!q.empty()) {  // 队列非空就继续扩展
            auto p = q.front();  // 取队首停靠点
            q.pop();  // 弹出队首
            int i = p.first, j = p.second;  // 拆出当前停靠点的坐标
            for (auto& dir : dirs) {  // 依次尝试四个方向
                int a = dir[0], b = dir[1];  // 方向对应的行增量与列增量
                char d = (char) dir[2];  // 该方向对应的字母，用于拼接路径
                int x = i, y = j;  // 从当前停靠点出发开始滚动
                int step = dist[i][j];  // 滚动距离从当前停靠点已有的最优距离起步
                while (x + a >= 0 && x + a < m && y + b >= 0 && y + b < n && maze[x + a][y + b] == 0 && (x != rh || y != ch)) {  // 沿该方向一路滚到底：下一格合法、不是墙，且当前还没进洞就继续
                    x += a;  // 行坐标前进一格
                    y += b;  // 列坐标前进一格
                    ++step;  // 滚动距离加一
                }  // 球在此处停下，得到一个新的停靠状态 (x, y)
                if (dist[x][y] > step || (dist[x][y] == step && (path[i][j] + d < path[x][y]))) {  // 距离更短，或距离相同但路径字典序更小才更新，保证答案最短且字典序最小
                    dist[x][y] = step;  // 更新最短距离
                    path[x][y] = path[i][j] + d;  // 路径末尾拼上本步方向的字母
                    if (x != rh || y != ch) q.push({x, y});  // 已经进洞就停止扩散，否则把新停靠点入队继续搜索
                }  // 条件更新分支结束
            }  // 四个方向尝试完毕
        }  // 队列处理完毕
        return path[rh][ch] == "" ? "impossible" : path[rh][ch];  // 洞的路径仍为空串说明无法到达，按题意返回 impossible
    }  // 方法体结束
};  // 类定义结束