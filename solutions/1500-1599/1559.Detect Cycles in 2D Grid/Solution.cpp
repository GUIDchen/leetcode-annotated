// 题目：1559. 二维网格图中探测环（Detect Cycles in 2D Grid）
// 思路：对每个未访问的同字符连通块做 BFS，队列里额外记录来源格子以排除无向边的回头路；一旦遇到同字符且已访问的相邻格子，就说明存在另一条路径，即成环。
// 时间复杂度：O(m·n)，每个格子至多入队一次；空间复杂度：O(m·n)，访问数组与队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool containsCycle(vector<vector<char>>& grid) {  // grid：字符矩阵；判断同字符格子能否连成一个环
        int m = grid.size(), n = grid[0].size();  // m 为行数，n 为列数
        vector<vector<bool>> vis(m, vector<bool>(n));  // vis[i][j] 标记格子 (i, j) 是否已被访问
        const vector<int> dirs = {-1, 0, 1, 0, -1};  // 方向数组：相邻两项组成「上、右、下、左」四个方向向量

        for (int i = 0; i < m; ++i) {  // 枚举行
            for (int j = 0; j < n; ++j) {  // 枚举列
                if (!vis[i][j]) {  // 未访问的格子是一个新的同字符连通块的起点
                    queue<array<int, 4>> q;  // 队列元素：{当前行, 当前列, 来源行, 来源列}
                    q.push({i, j, -1, -1});  // 起点没有来源，来源坐标记作 -1
                    vis[i][j] = true;  // 入队时就标记已访问，避免同一格子被重复入队

                    while (!q.empty()) {  // BFS 遍历整个连通块
                        auto p = q.front();  // 取队首元素
                        q.pop();  // 弹出队首
                        int x = p[0], y = p[1], px = p[2], py = p[3];  // 拆出当前格子坐标与来源格子坐标（来源用于排除回头路）

                        for (int k = 0; k < 4; ++k) {  // 依次尝试四个方向
                            int nx = x + dirs[k], ny = y + dirs[k + 1];  // 相邻格子的坐标（dirs 相邻两项就是一个方向向量）
                            if (nx >= 0 && nx < m && ny >= 0 && ny < n) {  // 保证相邻格子仍在矩阵内
                                if (grid[nx][ny] != grid[x][y] || (nx == px && ny == py)) {  // 字符不同说明不在同一个同字符块；走回来源格子属于同一条无向边，也要跳过
                                    continue;  // 这两种情况都不构成新的走向，直接看下一个方向
                                }  // 越界/非法分支结束
                                if (vis[nx][ny]) {  // 同字符且已被访问，说明从另一条路径也能到达，形成环
                                    return true;  // 找到环，立即返回
                                }  // if 结束
                                q.push({nx, ny, x, y});  // 入队，并把当前格子记为它的来源
                                vis[nx][ny] = true;  // 标记已访问
                            }  // 越界判断结束
                        }  // 四个方向遍历结束
                    }  // BFS 结束
                }  // if 结束
            }  // 列循环结束
        }  // 行循环结束
        return false;  // 所有连通块都无环
    }  // 方法结束
};  // 类定义结束
