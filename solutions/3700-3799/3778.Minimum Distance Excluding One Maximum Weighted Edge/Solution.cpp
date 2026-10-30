// 3778. 排除一个最大权重边的最小距离 / Minimum Distance Excluding One Maximum Weighted Edge
// 核心思路：把“可以免掉一条边的权重”建成第二维状态，在 (节点, 是否已用免费边) 的图上跑 Dijkstra，第一次弹到终点且已用掉免费边时即为答案。
// 复杂度：时间复杂度 O(m log n)，空间复杂度 O(n)，其中 n 为节点数，m 为边数。
class Solution {  // 定义题解类
public:  // 公有成员
    long long minCostExcludingMax(int n, vector<vector<int>>& edges) {  // 返回从 0 到 n-1、且免费经过一条边的最短距离
        vector<vector<pair<int, int>>> g(n);  // 邻接表：g[u] 保存 (相邻点, 边权)
        for (auto& e : edges) {  // 逐条边建立无向图
            int u = e[0], v = e[1], w = e[2];  // 拆出两个端点与权重
            g[u].push_back({v, w});  // 加入 u -> v
            g[v].push_back({u, w});  // 加入 v -> u
        }  // 建图结束

        long long inf = LLONG_MAX / 4;  // 用一个足够大的数表示无穷
        vector<array<long long, 2>> dist(n, {inf, inf});  // dist[u][used]：到达 u 且是否已用掉“免费边”的最短路
        dist[0][0] = 0;  // 起点 0，尚未使用免费边

        priority_queue<array<long long, 3>, vector<array<long long, 3>>, greater<array<long long, 3>>> pq;  // 小根堆，元素为 (距离, 节点, 是否已用免费边)
        pq.push({0, 0, 0});  // 起点状态入堆

        while (!pq.empty()) {  // Dijkstra 主循环
            auto t = pq.top();  // 取出当前距离最小的状态
            pq.pop();  // 弹出堆顶
            long long cur = t[0];  // 当前距离
            int u = t[1];  // 当前节点
            int used = t[2];  // 是否已经免费过一条边

            if (cur > dist[u][used]) {  // 该状态已被更优解取代
                continue;  // 直接跳过
            }  // 判断结束
            if (u == n - 1 && used == 1) {  // 到达终点且已用掉免费边
                return cur;  // 当前距离即为答案
            }  // 判断结束

            for (auto [v, w] : g[u]) {  // 遍历当前节点的所有相邻边
                long long nxt = cur + w;  // 正常支付这条边的代价
                if (nxt < dist[v][used]) {  // 可以松弛就更新
                    dist[v][used] = nxt;  // 更新最短路
                    pq.push({nxt, v, used});  // 新状态入堆
                }  // 松弛判断结束

                if (used == 0) {  // 还没用过免费边
                    nxt = cur;  // 把这条边当作最大权重边免掉
                    if (nxt < dist[v][1]) {  // 可以松弛就更新
                        dist[v][1] = nxt;  // 更新用掉免费边后的最短路
                        pq.push({nxt, v, 1});  // 新状态入堆
                    }  // 松弛判断结束
                }  // 贪心分支结束
            }  // 相邻边遍历结束
        }  // 主循环结束

        return dist[n - 1][1];  // 返回终点的答案
    }  // 方法结束
};  // 类定义结束
