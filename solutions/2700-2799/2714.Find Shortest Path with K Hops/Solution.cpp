// 题目：2714. 找到 K 次跨越的最短路径（Find Shortest Path with K Hops）
// 思路：把状态扩成 (节点, 已用跨越次数)，在分层图上跑 Dijkstra；普通边花 w，跨越边花 0 但次数 +1。
// 时间复杂度：O(k(n+m) log(kn))，状态数 n(k+1)；空间复杂度：O(nk+m)，dist 数组与邻接表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int shortestPathWithHops(int n, vector<vector<int>>& edges, int s, int d, int k) {  // n 为节点数，edges 为无向带权边，s 起点、d 终点、k 最多可跨越次数
        vector<pair<int, int>> g[n];  // 邻接表：g[u] 存放 (相邻点, 边权)
        for (auto& e : edges) {  // 逐条读入无向边
            int u = e[0], v = e[1], w = e[2];  // 拆出端点 u、v 与边权 w
            g[u].emplace_back(v, w);  // 正向建边 u -> v
            g[v].emplace_back(u, w);  // 反向建边 v -> u
        }
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;  // 小根堆，元素为 (当前花费, 节点, 已用跨越次数)，按字典序取最小
        pq.emplace(0, s, 0);  // 起点入堆：花费 0、位于 s、还没用跨越
        int dist[n][k + 1];  // dist[v][t]：到达 v 且恰好用了 t 次跨越的最小花费
        memset(dist, 0x3f, sizeof(dist));  // 用 0x3f 填充成足够大的 INF，表示尚未到达
        dist[s][0] = 0;  // 起点的初始状态花费为 0
        while (!pq.empty()) {  // 堆非空就继续松弛
            auto [dis, u, t] = pq.top();  // 取出当前花费最小的状态
            pq.pop();  // 弹出堆顶，之后该状态可能被更优值覆盖
            for (auto [v, w] : g[u]) {  // 枚举 u 的所有出边
                if (t + 1 <= k && dist[v][t + 1] > dis) {  // 用一次跨越直接到 v：不花边权，只把次数 +1，且不能超过 k
                    dist[v][t + 1] = dis;  // 用零花费更新「跨越后」的状态
                    pq.emplace(dis, v, t + 1);  // 新状态入堆，供后续继续扩展
                }
                if (dist[v][t] > dis + w) {  // 不跨越，正常走这条边，花费加上边权 w
                    dist[v][t] = dis + w;  // 更新「不跨越」状态的最小花费
                    pq.emplace(dis + w, v, t);  // 新状态入堆
                }
            }
        }
        return *min_element(dist[d], dist[d] + k + 1);  // 终点 d 在任意跨越次数下的最小花费就是答案
    }
};