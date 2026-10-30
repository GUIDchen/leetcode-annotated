// 题目：882. 细分图中的可到达节点（Reachable Nodes In Subdivided Graph）
// 思路：把每条边拆成 cnt+1 段后跑 Dijkstra，求出到每个原图节点的最少步数；原图节点按 maxMoves 统计，每条边内部再用两端剩余步数分段计算。
// 时间复杂度：O((n + m) log n)，堆优化 Dijkstra；空间复杂度：O(n + m)，邻接表与距离数组。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {  // edges：{u, v, cnt} 表示 u 与 v 之间有 cnt 个细分节点；maxMoves：最大步数；n：原图节点数
        using pii = pair<int, int>;  // 简写：pair<距离, 节点>
        vector<vector<pii>> g(n);  // 邻接表；每条边相邻两节点之间实际要走 cnt+1 步
        for (auto& e : edges) {  // 逐条边建图
            int u = e[0], v = e[1], cnt = e[2] + 1;  // cnt+1 就是两端点之间的实际步数
            g[u].emplace_back(v, cnt);  // 加入 u→v 的边，权值为实际步数
            g[v].emplace_back(u, cnt);  // 加入 v→u 的反向边，权值相同（无向图）
        }
        priority_queue<pii, vector<pii>, greater<pii>> q;  // 小根堆，按距离从小到大出队（Dijkstra 的堆优化）
        q.emplace(0, 0);  // 起点 0 的距离为 0
        int dist[n];  // dist[i] 表示从 0 号节点到原图节点 i 的最少步数
        memset(dist, 0x3f, sizeof dist);  // 全部初始化为一个很大的值（0x3f3f3f3f）
        dist[0] = 0;  // 起点到自身距离为 0
        while (!q.empty()) {  // Dijkstra 主循环
            auto [d, u] = q.top();  // 取出当前距离最小的节点
            q.pop();  // 弹出堆顶
            for (auto& [v, cnt] : g[u]) {  // 松弛 u 的所有邻居
                if (d + cnt < dist[v]) {  // 找到一条更短的路径
                    dist[v] = d + cnt;  // 更新最短距离
                    q.emplace(dist[v], v);  // 新距离入堆，等待继续扩展
                }
            }
        }
        int ans = 0;  // ans：可到达的节点总数
        for (int& d : dist) ans += d <= maxMoves;  // 原图节点只要步数不超过 maxMoves 就算到达
        for (auto& e : edges) {  // 再统计每条边内部能到达的细分节点
            int u = e[0], v = e[1], cnt = e[2];  // 取出边的两端与细分节点数
            int a = min(cnt, max(0, maxMoves - dist[u]));  // 从 u 侧出发还能深入多少个细分节点
            int b = min(cnt, max(0, maxMoves - dist[v]));  // 从 v 侧出发还能深入多少个细分节点
            ans += min(cnt, a + b);  // 两侧合计不能超过这条边的细分节点总数
        }
        return ans;  // 返回可到达节点总数
    }  // 方法结束
};  // 类定义结束