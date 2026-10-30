// 题目：2290. 到达角落需要移除障碍物的最小数目（Minimum Obstacle Removal to Reach Corner）
// 核心思路：0-1 BFS。把格子当点、移动代价当边权（空地 0，障碍 1），用双端队列把 0 权边压队头、1 权边压队尾，保证按代价单调出队。
// 时间复杂度：O(mn)，每个格子最多入队常数次；空间复杂度：O(mn)，队列与访问标记各占 O(mn)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumObstacles(vector<vector<int>>& grid) {  // grid：0 表示空地、1 表示障碍；返回从左上到右下最少移除的障碍数
        int m = grid.size(), n = grid[0].size();  // m：行数；n：列数
        deque<tuple<int, int, int>> q{{0, 0, 0}};  // 双端队列元素是 (行, 列, 已移除障碍数)，起点 (0,0) 的代价为 0
        bool vis[m][n];  // 访问标记：记录每个格子是否已按最优代价出队处理过
        memset(vis, 0, sizeof vis);  // 全部清零（false），表示一开始所有格子都未访问
        int dirs[5] = {-1, 0, 1, 0, -1};  // 四方向偏移的紧凑写法：相邻两项 dirs[h]、dirs[h+1] 组成一个方向向量
        while (1) {  // 0-1 BFS 主循环：终点一定会先被弹出并返回，因此无需显式的终止条件
            auto [i, j, k] = q.front();  // 结构化绑定取出队头状态：位置 (i, j) 与已花的移除代价 k
            q.pop_front();  // 队头出队，准备扩展它的邻居
            if (i == m - 1 && j == n - 1) {  // 到达右下角终点
                return k;  // 双端队列保证按代价单调出队，此刻的 k 就是最小移除数
            }
            if (vis[i][j]) {  // 该格子此前已用更小或相同的代价处理过
                continue;  // 丢弃这个过期的重复状态
            }
            vis[i][j] = true;  // 标记已处理，保证每个格子只被扩展一次
            for (int h = 0; h < 4; ++h) {  // 枚举上下左右四个方向
                int x = i + dirs[h], y = j + dirs[h + 1];  // 邻居的行、列坐标
                if (x >= 0 && x < m && y >= 0 && y < n) {  // 越界的邻居直接跳过
                    if (grid[x][y] == 0) {  // 空地：走过去不需要移除任何障碍
                        q.push_front({x, y, k});  // 0 权边压到队头，让它和当前状态同层优先被处理
                    } else {  // 障碍格：走过去必须移除它
                        q.push_back({x, y, k + 1});  // 1 权边压到队尾，代价加一并排到后面处理
                    }
                }  // 结束四个方向的枚举
            }
        }  // 结束 0-1 BFS 主循环
    }  // 结束 minimumObstacles 方法
};  // 结束 Solution 类定义