// 题目：2814. 避免淹死并到达目的地的最短时间（Minimum Time Takes to Reach Destination Without Drowning）
// 思路：先以所有水域为源点做一次多源 BFS，算出每格的最早淹没时刻；再从起点 S 做 BFS，只在「第 t+1 秒踏入时水还没到」的格子上扩展，第一次到达 D 的时间就是答案。
// 时间复杂度：O(m×n)，两遍 BFS 中每格最多入队一次；空间复杂度：O(m×n)，淹没时刻表、访问标记、队列各占 O(m×n)。
class Solution {  // 题解类：网格 BFS 求解安全到达终点的最短时间
public:  // 题解方法对外可见
    int minimumSeconds(vector<vector<string>>& land) {  // land：字符网格，'.' 可走、'*' 水、'S' 起点、'D' 终点、'X' 石头；返回最短安全时间，无法到达返回 -1
        int m = land.size(), n = land[0].size();  // m、n 为行数与列数，后面所有边界判断都要用
        bool vis[m][n];  // 访问标记：BFS 时防止同一格重复入队（按判题器习惯使用变长数组）
        int g[m][n];  // g[i][j]：水域淹没该格的最早秒数；保持 0x3f3f3f3f 表示永远不会被淹
        memset(vis, false, sizeof(vis));  // 访问标记先全部置为 false
        memset(g, 0x3f, sizeof(g));  // 淹没时刻先全部置为「无穷大」，即默认安全
        queue<pair<int, int>> q;  // BFS 队列，元素是坐标 (i, j)
        int si = 0, sj = 0;  // 起点 'S' 的坐标；题目保证存在，这里先给 0 只是初始化
        for (int i = 0; i < m; ++i) {  // 第一遍扫描：把所有水域入队（多源 BFS），同时记下起点位置
            for (int j = 0; j < n; ++j) {  // 遍历每一列
                auto c = land[i][j];  // 取出当前格子的字符，避免重复访问 land[i][j]
                if (c == "*") {  // 遇到水域：作为淹没扩散的源点
                    q.emplace(i, j);  // 水域入队，等待第一遍 BFS 从它开始扩散
                } else if (c == "S") {  // 遇到起点：只记录坐标，稍后第二遍 BFS 从它出发
                    si = i;  // 记下起点的行号
                    sj = j;  // 记下起点的列号
                }
            }  // 当前行扫描结束
        }  // 扫描完毕，队列里已经是所有水域
        int dirs[5] = {-1, 0, 1, 0, -1};  // 四方向增量，成对读取 (dirs[d], dirs[d+1]) 就是上、右、下、左
        for (int t = 0; !q.empty(); ++t) {  // 第一遍 BFS：第 t 秒扩散一层，求出每格的淹没时刻
            for (int k = q.size(); k; --k) {  // 先固定本层节点数，保证同一秒的格子被一起处理
                auto [i, j] = q.front();  // 取出队首坐标
                q.pop();  // 弹出队首，避免重复处理
                g[i][j] = t;  // 水在第 t 秒覆盖到该格（起点的淹没时刻同样被记录）
                for (int d = 0; d < 4; ++d) {  // 枚举四个方向
                    int x = i + dirs[d], y = j + dirs[d + 1];  // 计算邻居坐标
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y]) {  // 越界或已被淹没标记过的格子直接跳过
                        bool empty = land[x][y] == ".";  // 该格是普通空地
                        bool start = land[x][y] == "S";  // 该格是起点：水同样可以漫过它
                        if (empty || start) {  // 水只能漫过空地和起点；石头 'X'、终点 'D' 都不可被淹没
                            vis[x][y] = true;  // 标记已访问，防止同一格被多次入队
                            q.emplace(x, y);  // 入队，下一秒继续向外扩散
                        }
                    }
                }  // 本层四个方向处理完毕
            }  // 本层处理完毕
        }  // 队列空即所有可达格子都算完了淹没时刻
        q.emplace(si, sj);  // 第二遍 BFS：把起点放入队列，开始找去终点的最短路
        memset(vis, false, sizeof(vis));  // 复用 vis，先清掉第一遍 BFS 留下的标记
        vis[si][sj] = true;  // 起点标记为已访问
        for (int t = 0; !q.empty(); ++t) {  // 第二遍 BFS：第 t 秒能站到的格子
            for (int k = q.size(); k; --k) {  // 固定本层节点数，BFS 保证层内时间相同
                auto [i, j] = q.front();  // 取出队首坐标
                q.pop();  // 弹出队首
                if (land[i][j] == "D") {  // 一旦站在终点上就直接返回当前秒数（BFS 先到即最短）
                    return t;  // 返回最短安全时间
                }
                for (int d = 0; d < 4; ++d) {  // 枚举四个方向
                    int x = i + dirs[d], y = j + dirs[d + 1];  // 邻居坐标
                    if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y] && g[x][y] > t + 1) {  // 关键剪枝：第 t+1 秒踏入时必须还没被淹，即 g[x][y] > t+1；同时要未访问且不越界
                        bool empty = land[x][y] == ".";  // 邻居是空地
                        bool dest = land[x][y] == "D";  // 邻居是终点
                        if (empty || dest) {  // 只能进入空地或终点；石头 'X' 不可通行，起点也不必回头
                            vis[x][y] = true;  // 标记已访问
                            q.emplace(x, y);  // 入队，下一秒继续扩展
                        }
                    }
                }  // 四个方向处理完毕
            }  // 本层处理完毕
        }  // 队列空表示所有安全可达的格子都试过了
        return -1;  // 没能到达终点，按题意返回 -1
    }
};