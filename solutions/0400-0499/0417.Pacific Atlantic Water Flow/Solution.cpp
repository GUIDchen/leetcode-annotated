// 题目：417. 太平洋大西洋水流问题（Pacific Atlantic Water Flow）
// 思路：反向思考，从两个大洋的边界出发做 BFS，只走向「高度不低于当前格」的邻居；两次可达标记取交集就是答案。
// 时间复杂度：O(m * n)，每个格子最多入队一次；空间复杂度：O(m * n)，两个访问数组与两个队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {  // heights 是高度矩阵，返回高度上同时能流向太平洋和大西洋的所有坐标
        int m = heights.size(), n = heights[0].size();  // m 行、n 列
        vector<vector<bool>> vis1(m, vector<bool>(n, false)), vis2(m, vector<bool>(n, false));  // vis1/vis2 分别标记能否流到太平洋、大西洋
        queue<pair<int, int>> q1, q2;  // 两个 BFS 队列，种子分别是两个大洋的边界格
        vector<int> dirs = {-1, 0, 1, 0, -1};  // 方向数组：相邻两个数组成一个方向（上、右、下、左）

        for (int i = 0; i < m; ++i) {  // 遍历每一行，把最左列与最右列作为种子
            q1.emplace(i, 0);  // 最左列（太平洋一侧）入队
            vis1[i][0] = true;  // 标记最左列已访问
            q2.emplace(i, n - 1);  // 最右列（大西洋一侧）入队
            vis2[i][n - 1] = true;  // 标记最右列已访问
        }  // 行循环结束
        for (int j = 0; j < n; ++j) {  // 遍历每一列，把最上行与最下行作为种子
            q1.emplace(0, j);  // 最上行（太平洋一侧）入队
            vis1[0][j] = true;  // 标记最上行已访问
            q2.emplace(m - 1, j);  // 最下行（大西洋一侧）入队
            vis2[m - 1][j] = true;  // 标记最下行已访问
        }  // 列循环结束

        auto bfs = [&](queue<pair<int, int>>& q, vector<vector<bool>>& vis) {  // 定义 BFS：从队列中的格子出发，向高度不低于当前格的邻居扩散
            while (!q.empty()) {  // 队列非空就继续扩散
                auto [x, y] = q.front();  // 取出队首坐标（结构化绑定拆成 x、y）
                q.pop();  // 弹出队首元素
                for (int k = 0; k < 4; ++k) {  // 枚举四个方向
                    int nx = x + dirs[k], ny = y + dirs[k + 1];  // 计算邻居坐标
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n  // 邻居必须仍在网格内（行）
                        && !vis[nx][ny]  // 且这个邻居还没被访问过
                        && heights[nx][ny] >= heights[x][y]) {  // 且邻居高度不低于当前格（反向看：水能从邻居流到当前格）
                        vis[nx][ny] = true;  // 标记邻居可从该大洋到达
                        q.emplace(nx, ny);  // 邻居入队，继续往外扩散
                    }  // 当前方向处理结束
                }  // 四个方向枚举结束
            }  // 队列清空，本次 BFS 结束
        };  // lambda 定义结束

        bfs(q1, vis1);  // 从太平洋边界出发，标记所有能流到太平洋的格子
        bfs(q2, vis2);  // 从大西洋边界出发，标记所有能流到大西洋的格子

        vector<vector<int>> ans;  // 用于存放答案的坐标列表
        for (int i = 0; i < m; ++i)  // 遍历每一行
            for (int j = 0; j < n; ++j)  // 遍历每一列
                if (vis1[i][j] && vis2[i][j])  // 两个大洋都能到达的格子就是答案
                    ans.push_back({i, j});  // 把坐标加入答案
        return ans;  // 返回所有满足条件的坐标
    }  // pacificAtlantic 方法结束
};  // Solution 类结束
