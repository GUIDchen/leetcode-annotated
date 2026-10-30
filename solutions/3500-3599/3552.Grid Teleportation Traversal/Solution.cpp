// 题目：3552. 网格传送门旅游（Grid Teleportation Traversal）
// 思路：把“走到相邻格”看作权 1 的边、“使用传送门跳到同字母格”看作权 0 的边，用 0-1 BFS 求最短路：权 0 的转移压入队首、权 1 的压入队尾；每种字母的传送门只展开一次，整体复杂度保持线性。
// 时间复杂度：O(m·n)，每个格子最多入队常数次、每个传送门只展开一次；空间复杂度：O(m·n)，存放距离数组与队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minMoves(vector<string>& matrix) {  // matrix：字符网格；返回从左上角走到右下角的最少移动次数
        int m = matrix.size(), n = matrix[0].size();  // m、n：网格的行数与列数
        unordered_map<char, vector<pair<int, int>>> g;  // g：传送门字符 -> 该字符的所有格子坐标
        for (int i = 0; i < m; ++i)  // 枚举行下标 i
            for (int j = 0; j < n; ++j) {  // 枚举行内列下标 j
                char c = matrix[i][j];  // c：当前格子的字符
                if (isalpha(c)) g[c].push_back({i, j});  // 字母表示传送门，按字符归类收集坐标
            }  // 双行循环结束
        int dirs[5] = {-1, 0, 1, 0, -1};  // 四方向偏移，相邻两项配成一个方向 (dx, dy)
        int INF = numeric_limits<int>::max() / 2;  // INF：取最大值的一半作“无穷”，相加时不会溢出
        vector<vector<int>> dist(m, vector<int>(n, INF));  // dist[i][j]：从起点到达 (i,j) 的最少移动次数
        dist[0][0] = 0;  // 起点距离为 0
        deque<pair<int, int>> q;  // 0-1 BFS 使用的双端队列
        q.push_back({0, 0});  // 起点入队，等待扩展
        while (!q.empty()) {  // 队列非空就继续扩展
            auto [i, j] = q.front();  // 取出队首坐标（结构化绑定）
            q.pop_front();  // 队首出队
            int d = dist[i][j];  // d：到达当前格子的最少移动次数
            if (i == m - 1 && j == n - 1) return d;  // 到达终点，0-1 BFS 的出队顺序保证这就是最短路
            char c = matrix[i][j];  // c：当前格子上的字符
            if (g.count(c)) {  // 当前格子是传送门，且该字符还未被展开过
                for (auto [x, y] : g[c])  // 枚举同字符的所有传送目标格
                    if (d < dist[x][y]) {  // 若经由传送门到达更优才更新
                        dist[x][y] = d;  // 传送不消耗移动次数，距离保持为 d
                        q.push_front({x, y});  // 边权为 0，压入队首以维持队列的单调性
                    }  // 可用目标更新完毕
                g.erase(c);  // 同一字符的传送门只需展开一次，删除后再用不会更优
            }  // 传送门分支结束
            for (int idx = 0; idx < 4; ++idx) {  // 枚举四个相邻方向
                int x = i + dirs[idx], y = j + dirs[idx + 1];  // 相邻格子的坐标 (x, y)
                if (0 <= x && x < m && 0 <= y && y < n && matrix[x][y] != '#' && d + 1 < dist[x][y]) {  // 不越界、不是障碍且能刷新更短距离时才走这一步
                    dist[x][y] = d + 1;  // 走一步代价为 1
                    q.push_back({x, y});  // 边权为 1，压入队尾
                }  // 本方向处理结束
            }  // 四方向处理结束
        }  // 队列耗尽仍未到达终点
        return -1;  // 无法到达右下角
    }  // 方法结束
};  // 类定义结束
