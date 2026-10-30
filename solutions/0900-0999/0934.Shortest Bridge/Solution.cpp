// 题目：934. 最短的桥（Shortest Bridge）
// 思路：先 DFS 把第一座岛整块染色并入队，再用多源 BFS 逐层向外扩张海水，第一次碰到第二座岛时的层数就是最短桥长。
// 时间复杂度：O(n^2)，每个格子最多被访问常数次；空间复杂度：O(n^2)，队列与递归栈最坏会存下整个网格。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    const static inline vector<int> dirs = {-1, 0, 1, 0, -1};  // 四方向偏移量，相邻两个数组成一个 (dx, dy) 方向

    int shortestBridge(vector<vector<int>>& grid) {  // grid 中 1 是陆地、0 是海水；返回连接两座岛所需翻转的最小 0 的个数
        int n = grid.size();  // 网格边长
        queue<pair<int, int>> q;  // 多源 BFS 队列：先装第一座岛的所有格子，再装逐层扩张到的海水
        function<void(int, int)> dfs = [&](int i, int j) {  // 递归 lambda：把与 (i, j) 连通的第一座岛整块标记并收集进队列
            grid[i][j] = 2;  // 标 2 表示“属于第一座岛且已访问”，避免 DFS 重复进入
            q.emplace(i, j);  // 入队，作为多源 BFS 的起点之一
            for (int k = 0; k < 4; ++k) {  // 枚举四个相邻方向
                int x = i + dirs[k], y = j + dirs[k + 1];  // 相邻格子的坐标
                if (x >= 0 && x < n && y >= 0 && y < n && grid[x][y] == 1) {  // 先做边界检查，再判断是否仍是未访问的陆地
                    dfs(x, y);  // 继续向同岛的其它陆地扩散
                }
            }
        };  // lambda 定义结束
        for (int i = 0, x = 1; i < n && x; ++i) {  // x 是“还没找到第一座岛”的标志，找到后置 0 以便提前结束外层循环
            for (int j = 0; j < n; ++j) {  // 逐列扫描当前行
                if (grid[i][j]) {  // 遇到值为 1 的陆地，说明第一座岛的第一个格子找到了
                    dfs(i, j);  // 用 DFS 把整座岛染色并全部入队
                    x = 0;  // 清空标志，让外层循环在下一次条件判断时退出
                    break;  // 已经处理完第一座岛，跳出内层循环
                }
            }
        }
        int ans = 0;  // ans 记录当前已扩张的海水层数，也就是桥长
        while (1) {  // 循环直到某次扩张碰到第二座岛并直接 return
            for (int h = q.size(); h; --h) {  // h 为本层待处理的格子数，先把这一层全部处理完，层数才不会错乱
                auto [i, j] = q.front();  // 取出队首格子
                q.pop();  // 出队
                for (int k = 0; k < 4; ++k) {  // 枚举四个相邻方向
                    int x = i + dirs[k], y = j + dirs[k + 1];  // 相邻格子的坐标
                    if (x >= 0 && x < n && y >= 0 && y < n) {  // 只处理网格内的格子
                        if (grid[x][y] == 1) return ans;  // 遇到 1 说明到达第二座岛，当前层数就是最短桥长
                        if (grid[x][y] == 0) {  // 遇到 0 说明是可扩张的海水
                            grid[x][y] = 2;  // 把海水标成 2，表示已经访问，防止重复入队
                            q.emplace(x, y);  // 海水入队，作为下一层继续扩张的起点
                        }
                    }
                }
            }
            ++ans;  // 一整层扩张完，桥长加一
        }
    }
};