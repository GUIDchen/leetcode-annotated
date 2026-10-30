// 题目：1926. 迷宫中离入口最近的出口（Nearest Exit from Entrance in Maze）
// 思路：从入口开始做分层 BFS 逐层扩散，第一次走到边界上的空格子时，当前层数就是最近出口的步数。
// 时间复杂度：O(mn)，每个格子最多入队一次；空间复杂度：O(mn)，队列最坏要存下所有格子。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {  // maze：迷宫网格；entrance：入口坐标
        int m = maze.size(), n = maze[0].size();  // m 是行数，n 是列数
        int dirs[5] = {-1, 0, 1, 0, -1};  // 方向增量数组，前后相邻两项组成上下左右四个方向
        queue<pair<int, int>> q;  // BFS 队列，存放待扩展的坐标
        q.emplace(entrance[0], entrance[1]);  // 入口先进队作为第一层
        maze[entrance[0]][entrance[1]] = '+';  // 把入口改成墙，表示已访问，避免绕回来
        for (int ans = 1; !q.empty(); ++ans) {  // ans 是扩散步数，队列空则说明搜完
            for (int k = q.size(); k; --k) {  // 只处理当前层的 k 个节点，保证按层推进
                auto [i, j] = q.front();  // 取出队首坐标（结构化绑定）
                q.pop();  // 队首出队
                for (int d = 0; d < 4; ++d) {  // 枚举四个方向
                    int x = i + dirs[d], y = j + dirs[d + 1];  // 邻居坐标
                    if (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == '.') {  // 邻居在界内且是未访问的空格子
                        if (x == 0 || x == m - 1 || y == 0 || y == n - 1) {  // 这个空格子位于迷宫边界，就是出口
                            return ans;  // 分层 BFS 保证第一次遇到出口即最近
                        }
                        maze[x][y] = '+';  // 入队前标记为已访问，防止后续重复扩展
                        q.emplace(x, y);  // 合法邻居进入下一层
                    }
                }
            }
        }
        return -1;  // 队列耗尽仍未找到出口
    }
};
