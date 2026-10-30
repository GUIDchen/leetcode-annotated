// 题目：1368. 使网格图至少有一条有效路径的最小代价（Minimum Cost to Make at Least One Valid Path in a Grid）
// 思路：0-1 BFS（双端队列）。沿当前箭头走代价为 0 入队首，改箭头代价为 1 入队尾，第一次到达终点时的代价即最小。
// 时间复杂度：O(m·n)，每格最多出队一次；空间复杂度：O(m·n)，vis 与队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minCost(vector<vector<int>>& grid) {  // grid：每格记录箭头方向（1 右、2 左、3 下、4 上）
        int m = grid.size(), n = grid[0].size();  // m、n 分别是网格的行数与列数
        vector<vector<bool>> vis(m, vector<bool>(n));  // vis[i][j] 表示格子 (i, j) 是否已出队处理过
        vector<vector<int>> dirs = {{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};  // dirs 下标 1~4 与箭头编号对应：右、左、下、上
        deque<pair<int, int>> q;  // 双端队列，元素为 (格子编号 i*n+j, 到达该格的代价 d)
        q.push_back({0, 0});  // 从左上角 (0, 0) 出发，初始代价 0
        while (!q.empty()) {  // 队列非空就继续扩展
            auto p = q.front();  // 取队首元素
            q.pop_front();  // 弹出队首元素
            int i = p.first / n, j = p.first % n, d = p.second;  // 把一维编号拆回坐标 i、j，d 是到达该格的代价
            if (i == m - 1 && j == n - 1) return d;  // 到达右下角，0-1 BFS 保证此时的 d 就是最小代价
            if (vis[i][j]) continue;  // 该格子已处理过，跳过
            vis[i][j] = true;  // 标记为已处理
            for (int k = 1; k <= 4; ++k) {  // 枚举四个方向
                int x = i + dirs[k][0], y = j + dirs[k][1];  // 候选邻格 (x, y)
                if (x >= 0 && x < m && y >= 0 && y < n) {  // 判断邻格是否仍在网格内
                    if (grid[i][j] == k)  // 当前格箭头正好指向 k，可以不付代价走这一步
                        q.push_front({x * n + y, d});  // 代价不变，放到队首（0-1 BFS 的关键）
                    else  // 否则需要改一次箭头方向
                        q.push_back({x * n + y, d + 1});  // 代价加 1，放到队尾
                }  // 边界判断结束
            }  // 方向循环结束
        }  // 队列循环结束
        return -1;  // 队列耗尽仍未到达终点，返回 -1
    }  // 方法结束
};  // 类定义结束