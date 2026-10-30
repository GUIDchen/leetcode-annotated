// 题目：1730. 获取食物的最短路径（Shortest Path to Get Food）
// 思路：从 '*' 出发做 BFS，逐层扩散并就地标记访问过的空地，第一次遇到 '#' 时的层数就是最短距离。
// 时间复杂度：O(m*n)，每个格子最多入队一次；空间复杂度：O(m*n)，队列最坏存下所有空地。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    const static inline vector<int> dirs = {-1, 0, 1, 0, -1};  // 四方向增量表：相邻两项组成 (dx, dy)

    int getFood(vector<vector<char>>& grid) {  // grid：'*' 是起点、'#' 是食物、'O' 是空地、'X' 是障碍
        int m = grid.size(), n = grid[0].size();  // m 是行数，n 是列数
        queue<pair<int, int>> q;  // BFS 队列，存放待扩展的坐标
        for (int i = 0, x = 1; i < m && x == 1; ++i) {  // x 是「还没找到起点」的标志，找到后靠它提前结束外层循环
            for (int j = 0; j < n; ++j) {  // 逐列扫描当前行
                if (grid[i][j] == '*') {  // 找到起点
                    q.emplace(i, j);  // 起点入队
                    x = 0;  // 标记已找到，外层循环条件随之失效
                    break;  // 跳出内层扫描
                }  // 起点判断结束
            }  // 内层扫描结束
        }  // 起点的行扫描结束
        int ans = 0;  // 已经走过的步数
        while (!q.empty()) {  // 队列非空就继续按层扩展
            ++ans;  // 进入下一层，步数加一
            for (int t = q.size(); t; --t) {  // 只处理当前层的节点，避免层与层混在一起
                auto [i, j] = q.front();  // 取出队头坐标
                q.pop();  // 弹出队头
                for (int k = 0; k < 4; ++k) {  // 枚举四个方向
                    int x = i + dirs[k], y = j + dirs[k + 1];  // 相邻格子的坐标
                    if (x >= 0 && x < m && y >= 0 && y < n) {  // 未越界才继续判断
                        if (grid[x][y] == '#') return ans;  // 遇到食物，当前步数就是最短距离
                        if (grid[x][y] == 'O') {  // 只有空地可以继续走
                            grid[x][y] = 'X';  // 就地标记为已访问，防止重复入队
                            q.emplace(x, y);  // 入队等待下一层扩展
                        }  // 空地判断结束
                    }  // 边界判断结束
                }  // 方向枚举结束
            }  // 当前层处理完毕
        }  // 队列清空
        return -1;  // 走不到食物，按题目要求返回 -1
    }  // 方法结束
};  // 类结束