// 题目：675. 为高尔夫比赛砍树（Cut Off Trees for Golf Event）
// 思路：树必须按高度升序砍，故先把所有树排序；相邻两棵树之间用 A*（曼哈顿距离作启发函数）求最短步数，累计求和，任一段不可达就返回 -1。
// 时间复杂度：O(T * m * n log(mn))，T 为树的个数，每段做一次 A* 最坏遍历整个网格；空间复杂度：O(m * n)，距离数组与堆。
class Solution {  // LeetCode 约定的题解类
public:  // 下面成员对外可见
    int m;  // 森林的行数
    int n;  // 森林的列数
    vector<int> dist;  // 距离数组，用「行 * n + 列」的一维编号索引

    int cutOffTree(vector<vector<int>>& forest) {  // forest：网格，0 表示不可通行，1 表示草地，大于 1 表示树
        m = forest.size();  // 记录行数
        n = forest[0].size();  // 记录列数
        dist.resize(3600);  // 预分配距离数组，3600 覆盖 50 * 50 的网格上限
        vector<pair<int, int>> trees;  // 收集所有树：(树高, 一维坐标)
        for (int i = 0; i < m; ++i)  // 枚举行
            for (int j = 0; j < n; ++j)  // 枚举列
                if (forest[i][j] > 1)  // 值大于 1 才是树
                    trees.push_back({forest[i][j], i * n + j});  // 记录树高与一维坐标
        sort(trees.begin(), trees.end());  // 按树高升序排序，得到唯一的砍树顺序
        int ans = 0;  // 累计总步数
        int start = 0;  // 起点：左上角 (0, 0) 的一维坐标
        for (auto& tree : trees) {  // 按从矮到高的顺序依次砍树
            int end = tree.second;  // 当前目标树的一维坐标
            int t = bfs(start, end, forest);  // 求从当前位置到目标树的最短步数
            if (t == -1) return -1;  // 走不到说明无法完成比赛
            ans += t;  // 累加这一段步数
            start = end;  // 起点移动到刚砍完的树的位置
        }
        return ans;  // 返回砍完所有树的总步数
    }

    int bfs(int start, int end, vector<vector<int>>& forest) {  // A* 搜索：start 到 end 的最短步数
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;  // 小根堆，按 (f = g + h) 出队
        q.push({f(start, end), start});  // 起点入堆，此时 g = 0，f 就是启发值
        fill(dist.begin(), dist.end(), INT_MAX);  // 所有距离先初始化为无穷大
        dist[start] = 0;  // 起点到自己的距离为 0
        vector<int> dirs = {-1, 0, 1, 0, -1};  // 四个方向的偏移，成对取值得到上下左右
        while (!q.empty()) {  // 堆不空就继续扩展
            int state = q.top().second;  // 取出 f 值最小的节点
            q.pop();  // 弹出该节点
            if (state == end) return dist[state];  // 第一次弹出终点即为最短距离
            for (int k = 0; k < 4; ++k) {  // 枚举四个相邻方向
                int x = state / n + dirs[k], y = state % n + dirs[k + 1];  // 一维坐标转二维后按方向移动
                if (x >= 0 && x < m && y >= 0 && y < n && forest[x][y] && dist[x * n + y] > dist[state] + 1) {  // 不越界、可通行、且能松弛
                    dist[x * n + y] = dist[state] + 1;  // 记录更短的步数
                    q.push({dist[x * n + y] + f(x * n + y, end), x * n + y});  // 用新的 f 值入堆
                }
            }
        }
        return -1;  // 搜完仍未到达终点，说明不可达
    }

    int f(int start, int end) {  // 启发函数：两点之间的曼哈顿距离
        int a = start / n, b = start % n;  // 起点的一维坐标还原为行列
        int c = end / n, d = end % n;  // 终点的一维坐标还原为行列
        return abs(a - c) + abs(b - d);  // 行差绝对值加列差绝对值
    }
};