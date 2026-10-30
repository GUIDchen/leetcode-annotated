// 3650. 边反转的最小路径总成本（Minimum Cost Path with Edge Reversals）
// 核心思路：把 u -> v 花费 w 的有向边补一条 v -> u 花费 2w 的反向边，转成有向正权图后用 Dijkstra 求 0 到 n-1 的最短路。
// 复杂度：时间 O((n + m) log n)，空间 O(n + m)，其中 m 为边数。
class Solution {  // 定义题解类
public:  // 公有接口
    int minCost(int n, vector<vector<int>>& edges) {  // 返回 0 到 n-1 的最小总成本；edges[i] = [u, v, w] 表示 u -> v 花费 w
        using pii = pair<int, int>;  // 堆中元素用 (距离, 节点) 二元组表示
        vector<vector<pii>> g(n);  // 邻接表：g[x] 保存从 x 出发的 (邻居, 边权)
        for (auto& e : edges) {  // 遍历每条有向边
            int u = e[0], v = e[1], w = e[2];  // 取出起点、终点与原始边权
            g[u].push_back({v, w});  // 正常方向：u -> v 花费 w
            g[v].push_back({u, w * 2});  // 反转方向：v -> u 花费 2w（在 v 使用一次开关反向穿过）
        }  // 建图完毕

        const int inf = INT_MAX / 2;  // 取 INT_MAX 的一半作为无穷大，避免后面加法溢出
        vector<int> dist(n, inf);  // dist[i] 表示从 0 走到 i 的当前最短距离
        dist[0] = 0;  // 起点走到自己花费 0

        priority_queue<pii, vector<pii>, greater<pii>> pq;  // 小根堆，按距离升序弹出
        pq.push({0, 0});  // 起点入堆

        while (!pq.empty()) {  // Dijkstra 主循环：堆不空说明还有可松弛的状态
            auto [d, u] = pq.top();  // 弹出当前距离最小的状态
            pq.pop();  // 该状态出堆
            if (d > dist[u]) {  // 若记录的距离已经过期（被更优距离取代）
                continue;  // 跳过这条失效记录
            }  // 过期判断结束
            if (u == n - 1) {  // 终点第一次出堆时，其距离就是最终最短距离
                return d;  // 直接返回该距离
            }  // 终点判断结束

            for (auto& [v, w] : g[u]) {  // 松弛 u 的所有出边
                int nd = d + w;  // 经过 u 走到 v 的候选距离
                if (nd < dist[v]) {  // 候选距离更优则更新
                    dist[v] = nd;  // 更新 v 的最短距离
                    pq.push({nd, v});  // 新状态入堆
                }  // 松弛判断结束
            }  // 出边遍历结束
        }  // 主循环结束
        return -1;  // 从 0 无法到达 n-1 时返回 -1
    }  // minCost 结束
};  // 类定义结束
