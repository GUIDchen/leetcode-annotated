// 题目：286. 墙与门（Walls and Gates）—— 把每个空房间填成到最近门的距离，门记 0，墙记 -1，空房间初值 INT_MAX。
// 核心思路：多源 BFS。先把所有门作为第 0 层一起入队，再逐层向外扩散，空房间第一次被到达时的层数就是最短距离。
// 时间复杂度：O(m·n)，每个格子最多入队一次；空间复杂度：O(m·n)，队列最坏情况下装下所有格子。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    void wallsAndGates(vector<vector<int>>& rooms) {  // rooms：房间矩阵，直接原地修改，不需要返回值
        int m = rooms.size();  // 行数
        int n = rooms[0].size();  // 列数（题意保证矩阵非空，可直接读第 0 行）
        queue<pair<int, int>> q;  // BFS 队列，元素是 (行, 列) 坐标
        for (int i = 0; i < m; ++i)  // 枚举每一行
            for (int j = 0; j < n; ++j)  // 枚举每一列
                if (rooms[i][j] == 0)  // 找到一扇门（距离为 0 的源头）
                    q.emplace(i, j);  // 门作为多源 BFS 的起点入队
        int d = 0;  // 当前已经扩散到的距离层数，0 表示站在门上
        vector<int> dirs = {-1, 0, 1, 0, -1};  // 四个方向的增量：上、右、下、左，相邻两项正好拼成一个 (dx, dy)
        while (!q.empty()) {  // 队列非空说明还有可达的空房间没被填过
            ++d;  // 进入下一层，距离加一
            for (int i = q.size(); i > 0; --i) {  // 先固定本层节点数 q.size()，保证只弹出本层节点、新入队的留到下一层
                auto p = q.front();  // 取出队首坐标
                q.pop();  // 弹出队首，避免重复处理
                for (int j = 0; j < 4; ++j) {  // 枚举四个相邻方向
                    int x = p.first + dirs[j];  // 邻居的行坐标
                    int y = p.second + dirs[j + 1];  // 邻居的列坐标
                    if (x >= 0 && x < m && y >= 0 && y < n && rooms[x][y] == INT_MAX) {  // 不越界，且是尚未访问的空房间（门和墙的值不是 INT_MAX，不会被覆盖）
                        rooms[x][y] = d;  // 第一次到达就是最短距离，直接写入层号 d
                        q.emplace(x, y);  // 作为下一层扩散的起点入队
                    }
                }  // 同一层内的所有节点扩散完毕
            }  // 本层处理完，继续下一层
        }  // 队列为空，所有可达空房间都已填好
    }  // 方法结束，结果已原地写在 rooms 中
};