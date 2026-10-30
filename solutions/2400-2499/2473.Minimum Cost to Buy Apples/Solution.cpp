// 题目：2473. 购买苹果的最低成本（Minimum Cost to Buy Apples）
// 思路：把 roads 建成无向带权图，对每个城市作为买苹果的地点跑一次 Dijkstra；走到 u 买苹果总花费 = appleCost[u] + dist[u]*(k+1)，因为每走一条边自己要吃 k 个、路上还要吃 1 个，取最小值。
// 时间复杂度：O(n * m log m)，相当于做 n 次 Dijkstra；空间复杂度：O(n + m)，存邻接表与距离数组。
using ll = long long;  // 类型简写：后面多次用到 64 位整数，防止花费溢出 int
using pii = pair<int, int>;  // 类型简写：堆里存 (距离, 顶点) 二元组

class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见，判题器据此调用
    const int inf = 0x3f3f3f3f;  // 无穷大常量，取 0x3f 系列便于用 memset 按字节初始化

    vector<long long> minCost(int n, vector<vector<int>>& roads, vector<int>& appleCost, int k) {  // n 为城市数，roads 为无向道路，appleCost 为各地苹果单价，k 为每走一条路自吃的苹果数
        vector<vector<pii>> g(n);  // 邻接表建图：g[u] 保存 (邻居, 边权) 列表
        for (auto& e : roads) {  // 逐条读入道路
            int a = e[0] - 1, b = e[1] - 1, c = e[2];  // 题目下标从 1 开始，这里统一转成从 0 开始
            g[a].push_back({b, c});  // a → b 的有向边
            g[b].push_back({a, c});  // b → a 的有向边，两条合起来构成无向图
        }  // 建图结束
        int dist[n];  // 距离数组，放在 lambda 外层复用，避免每次调用都重新分配
        auto dijkstra = [&](int u) {  // 以 u 为起点的单源最短路，返回在该起点买苹果的最小总花费
            memset(dist, 63, sizeof dist);  // 把每个字节置成 0x3f，等价于将 dist 全部初始化为无穷大
            priority_queue<pii, vector<pii>, greater<pii>> q;  // 小根堆，按距离从小到大出队，保证 Dijkstra 的正确性
            q.push({0, u});  // 起点入堆，到自身距离为 0
            dist[u] = 0;  // 起点到自身的距离确定为 0
            ll ans = LONG_MAX;  // 当前起点的最优花费，先设成 64 位最大值
            while (!q.empty()) {  // 堆非空就继续取距离最小的点扩展
                auto p = q.top();  // 堆顶是当前距离最小的 (距离, 顶点)
                q.pop();  // 弹出堆顶
                int d = p.first;  // d 是到该点的最短距离
                u = p.second;  // 把 u 复用为当前正在扩展的顶点
                ans = min(ans, appleCost[u] + 1ll * d * (k + 1));  // 在 u 买苹果的总价：苹果单价 + 路上消耗的苹果数；1ll 把乘法提升到 64 位避免溢出
                for (auto& ne : g[u]) {  // 遍历 u 的所有邻居
                    auto [v, w] = ne;  // 结构化绑定取出邻居 v 与边权 w
                    if (dist[v] > dist[u] + w) {  // 发现更短的路径才做松弛
                        dist[v] = dist[u] + w;  // 更新 v 的最短距离
                        q.push({dist[v], v});  // 把更新后的 v 重新入堆
                    }  // 松弛分支结束
                }  // 邻居遍历结束
            }  // 出堆循环结束，从 u 出发的最短路全部算完
            return ans;  // 返回该起点的最小总花费
        };  // lambda 定义结束
        vector<ll> ans(n);  // 每个城市对应一个答案
        for (int i = 0; i < n; ++i) ans[i] = dijkstra(i);  // 枚举每个城市作为买苹果的地点，分别跑一次 Dijkstra
        return ans;  // 返回所有城市的最优花费
    }  // 方法结束
};  // 类定义结束