// 题目：3112. 访问消失节点的最少时间（Minimum Time to Visit Disappearing Nodes）
// 思路：堆优化 Dijkstra 求最短路，松弛时额外要求「到达时间 < 该节点的消失时间」，这样已消失的点不会再向外扩展。
// 时间复杂度：O((n + m) log n)，m 为边数；空间复杂度：O(n + m)，存邻接表与距离数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {  // n 是点数，edges 是无向边表，disappear 是各点的消失时间
        vector<vector<pair<int, int>>> g(n);  // 邻接表：g[u] 中存放 {邻点 v, 边权 w}
        for (const auto& e : edges) {  // 把边表展开成无向图的邻接表
            int u = e[0], v = e[1], w = e[2];  // 拆出边的两个端点与权重
            g[u].push_back({v, w});  // 存正向边
            g[v].push_back({u, w});  // 存反向边，因为图是无向的
        }

        vector<int> dist(n, 1 << 30);  // 距离数组初始化为极大值（约 1e9）
        dist[0] = 0;  // 起点 0 到自身的距离为 0

        using pii = pair<int, int>;  // 简写：元素是 {距离, 节点编号}
        priority_queue<pii, vector<pii>, greater<pii>> pq;  // 小根堆，每次弹出距离最小的候选
        pq.push({0, 0});  // 起点入堆

        while (!pq.empty()) {  // 堆空说明所有可达点都已完成松弛
            auto [du, u] = pq.top();  // 取出当前距离最小的候选（du 为距离，u 为编号）
            pq.pop();  // 弹出该候选

            if (du > dist[u]) {  // 这是被更优值覆盖过的过期状态
                continue;  // 直接跳过，避免重复扩展
            }

            for (auto [v, w] : g[u]) {  // 枚举 u 的所有邻边
                if (dist[v] > dist[u] + w && dist[u] + w < disappear[v]) {  // 能走得更短，且到达时 v 还没有消失
                    dist[v] = dist[u] + w;  // 更新 v 的最短距离
                    pq.push({dist[v], v});  // 把新的候选距离入堆，供后续松弛
                }
            }
        }

        vector<int> ans(n);  // 存放最终答案
        for (int i = 0; i < n; ++i) {  // 逐个节点整理答案
            ans[i] = dist[i] < disappear[i] ? dist[i] : -1;  // 在消失前能到达就取距离，否则记为 -1
        }

        return ans;  // 返回每个节点的最少访问时间
    }
};