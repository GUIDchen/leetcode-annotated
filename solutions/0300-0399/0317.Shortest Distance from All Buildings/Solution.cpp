// 题目：317. 离建筑物最近的距离（Shortest Distance from All Buildings）
// 思路：以每个建筑为源点做一次 BFS，累计每个空地被多少个建筑到达以及距离总和，最后取「所有建筑都能到达」的空地中的最小距离和。
// 时间复杂度：O(B·m·n)，B 为建筑数量，每个建筑做一次 BFS；空间复杂度：O(m·n)，访问标记与两个累计矩阵。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int shortestDistance(vector<vector<int>>& grid) {  // grid：0 表示空地、1 表示建筑、2 表示障碍
        int m = grid.size();  // 行数
        int n = grid[0].size();  // 列数
        typedef pair<int, int> pii;  // 坐标类型别名
        queue<pii> q;  // BFS 队列
        int total = 0;  // 建筑总数，用来判断某块空地是否所有建筑都可达
        vector<vector<int>> cnt(m, vector<int>(n));  // cnt[i][j]：能到达 (i,j) 的建筑个数
        vector<vector<int>> dist(m, vector<int>(n));  // dist[i][j]：这些建筑到 (i,j) 的距离之和
        vector<int> dirs = {-1, 0, 1, 0, -1};  // 四方向偏移，相邻两个元素组成一个 (dx, dy)
        for (int i = 0; i < m; ++i) {  // 枚举每个格子寻找建筑
            for (int j = 0; j < n; ++j) {  // 内层枚举每一列
                if (grid[i][j] == 1) {  // 是建筑，就以它为源点做一次 BFS
                    ++total;  // 建筑数加一
                    q.push({i, j});  // 源点入队
                    vector<vector<bool>> vis(m, vector<bool>(n));  // 本次 BFS 的访问标记，避免重复统计同一块空地
                    int d = 0;  // 当前 BFS 的层数，也就是距离
                    while (!q.empty()) {  // 队列非空就继续扩展
                        ++d;  // 进入下一层，距离加一
                        for (int k = q.size(); k > 0; --k) {  // 一次只处理本层的 q.size() 个节点
                            auto p = q.front();  // 取队头
                            q.pop();  // 出队
                            for (int l = 0; l < 4; ++l) {  // 枚举四个方向
                                int x = p.first + dirs[l];  // 新格子的行坐标
                                int y = p.second + dirs[l + 1];  // 新格子的列坐标
                                if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 0 && !vis[x][y]) {  // 越界、障碍、已访问都跳过，只扩展空地且未访问的格子
                                    ++cnt[x][y];  // 该空地能被当前建筑到达，计数加一
                                    dist[x][y] += d;  // 把当前建筑到它的距离累加进去
                                    q.push({x, y});  // 入队，下一层继续扩展
                                    vis[x][y] = true;  // 标记已访问，防止重复计数
                                }
                            }
                        }
                    }
                }
            }
        }
        int ans = INT_MAX;  // 最小距离和，初始为无穷大
        for (int i = 0; i < m; ++i)  // 枚举所有格子
            for (int j = 0; j < n; ++j)  // 内层枚举每一列
                if (grid[i][j] == 0 && cnt[i][j] == total)  // 是空地且所有建筑都能到达
                    ans = min(ans, dist[i][j]);  // 更新最小距离和
        return ans == INT_MAX ? -1 : ans;  // 没有任何可行空地时返回 -1
    }
};