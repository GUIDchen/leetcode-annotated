// 题目：1091. 二进制矩阵中的最短路径（Shortest Path in Binary Matrix）
// 思路：从左上角出发做八方向 BFS，入队时直接把格子改成 1 当障碍（复用 grid 省掉 visited），队列第一次弹出右下角时的层数就是最短路径长度。
// 时间复杂度：O(n²)，每个格子最多入队一次；空间复杂度：O(n²)，队列最坏存下一层的全部格子。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {  // grid 中 0 可走、1 是障碍，返回最短路径经过的格子数
        if (grid[0][0]) {  // 起点就是障碍，根本无法出发
            return -1;  // 直接判无解
        }  // 结束起点判断
        int n = grid.size();  // 方阵边长
        grid[0][0] = 1;  // 把起点标记为已访问（直接改 grid，省一个 visited 数组）
        queue<pair<int, int>> q;  // BFS 队列，元素是格子的坐标
        q.emplace(0, 0);  // 起点入队
        for (int ans = 1; !q.empty(); ++ans) {  // ans 是当前层对应的路径长度（格子数），每处理完一层加一
            for (int k = q.size(); k; --k) {  // 先固定本层的节点数，保证一层一层向外扩散
                auto [i, j] = q.front();  // 取出队首坐标（结构化绑定）
                q.pop();  // 队首出队
                if (i == n - 1 && j == n - 1) {  // 到达右下角
                    return ans;  // BFS 首次到达即为最短路径
                }  // 结束到达判断
                for (int x = i - 1; x <= i + 1; ++x) {  // 枚举八邻域的行坐标
                    for (int y = j - 1; y <= j + 1; ++y) {  // 枚举八邻域的列坐标
                        if (x >= 0 && x < n && y >= 0 && y < n && !grid[x][y]) {  // 坐标不越界且该格子可走（值为 0）
                            grid[x][y] = 1;  // 入队前先标记为已访问，避免重复入队
                            q.emplace(x, y);  // 邻居入队，留到下一层扩展
                        }  // 结束列枚举
                    }  // 结束行枚举
                }  // 结束本层处理
            }  // 本层处理完，路径长度加一
        }  // 队列空了仍未到达右下角
        return -1;  // 说明无路可走，返回 -1
    }  // 结束方法体
};  // 类定义结束