// 题目：1810. 隐藏网格下的最小消耗路径（Minimum Path Cost in a Hidden Grid）
// 思路：先用 DFS 借 GridMaster 探明整张地图并记录每格花费，再在已知地图上跑 Dijkstra，求起点到终点的最小花费。
// 时间复杂度：O(V + E log V)，V 为可达格子数；空间复杂度：O(V)，用于存地图与距离表。
/**
 * // This is the GridMaster's API interface.
 * // You should not implement it, or speculate about its implementation
 * class GridMaster {
 *   public:
 *     bool canMove(char direction);
 *     int move(char direction);
 *     boolean isTarget();
 * };
 */  // 以上是 GridMaster 接口声明，属于题目提供的黑盒 API，不需要自己实现

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findShortestPath(GridMaster& master) {  // master：黑盒机器人，提供 canMove / move / isTarget 三个方法
        const int m = 200, n = 200;  // 地图边长上限，200 x 200 足够覆盖题目的数据范围
        const int sx = 100, sy = 100;  // 起点放在地图正中间，保证四个方向都有足够的探索空间
        const int INF = INT_MAX / 2;  // 用足够大的数表示不可达；除以 2 是为了相加时不会溢出
        int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：相邻两项组成 (dx, dy)，依次是上、右、下、左
        char s[4] = {'U', 'R', 'D', 'L'};  // 与 dirs 一一对应的方向字母，用来调用 GridMaster 的方法

        vector<vector<int>> g(m, vector<int>(n, -1));  // g[x][y] 记录该格的花费，-1 表示尚未探索或不能通行
        pair<int, int> target = {-1, -1};  // 目标格子坐标，(-1, -1) 表示还没有找到

        auto dfs = [&](this auto& dfs, int x, int y) -> void {  // 深度优先搜索：把机器人能到达的格子及其花费全部记录下来
            if (master.isTarget()) {  // 当前格就是目标终点
                target = {x, y};  // 记住终点的坐标
            }  // if 结束
            for (int k = 0; k < 4; ++k) {  // 依次尝试四个方向
                int dx = dirs[k], dy = dirs[k + 1];  // 取出该方向的横向与纵向增量
                int nx = x + dx, ny = y + dy;  // 相邻格的坐标
                if (0 <= nx && nx < m && 0 <= ny && ny < n && g[nx][ny] == -1 && master.canMove(s[k])) {  // 只有坐标合法、还没探索过、且机器人允许移动时才继续
                    g[nx][ny] = master.move(s[k]);  // 真正走过去，并把这一格的花费记进地图
                    dfs(nx, ny);  // 从新格子继续向下探索
                    master.move(s[(k + 2) % 4]);  // 回溯：沿反方向走回原格，保证机器人位置与实际坐标始终一致
                }  // if 结束
            }  // for 结束
        };  // dfs 定义结束

        g[sx][sy] = 0;  // 起点的花费记作 0
        dfs(sx, sy);  // 从起点出发，把整张可达地图探索一遍

        if (target.first == -1 && target.second == -1) {  // 探索结束仍未找到终点
            return -1;  // 终点不可达，按题意返回 -1
        }  // if 结束

        vector<vector<int>> dist(m, vector<int>(n, INF));  // 最短路距离表，先全部置为无穷大
        dist[sx][sy] = 0;  // 起点到自身的距离是 0

        using Node = tuple<int, int, int>;  // 堆元素类型：(当前累计花费, x, y)
        priority_queue<Node, vector<Node>, greater<Node>> pq;  // 小根堆；tuple 默认按字典序比较，花费最小的状态先出堆
        pq.emplace(0, sx, sy);  // 起点入堆

        while (!pq.empty()) {  // Dijkstra 主循环
            auto [w, x, y] = pq.top();  // 取出当前花费最小的状态
            pq.pop();  // 弹出堆顶元素
            if (x == target.first && y == target.second) {  // 第一次弹出终点，它的花费就是最短路
                return w;  // 返回到达终点所需的最小花费
            }  // if 结束
            if (w > dist[x][y]) {  // 这是一条过期的旧记录（该格已经有更优解）
                continue;  // 直接跳过，避免重复松弛
            }  // if 结束

            for (int k = 0; k < 4; ++k) {  // 尝试从当前格向四个方向走
                int nx = x + dirs[k], ny = y + dirs[k + 1];  // 相邻格的坐标
                if (0 <= nx && nx < m && 0 <= ny && ny < n && g[nx][ny] != -1) {  // 相邻格在地图内，且已被探索过（花费已知）
                    int nd = w + g[nx][ny];  // 走到相邻格后的累计花费
                    if (nd < dist[nx][ny]) {  // 只有更短才更新
                        dist[nx][ny] = nd;  // 记录新的最短距离
                        pq.emplace(nd, nx, ny);  // 把更优状态压入堆，供后续继续松弛
                    }  // if 结束
                }  // if 结束
            }  // for 结束
        }  // while 结束

        return -1;  // 堆空说明终点不可达
    }  // 方法结束
};  // 类定义结束
