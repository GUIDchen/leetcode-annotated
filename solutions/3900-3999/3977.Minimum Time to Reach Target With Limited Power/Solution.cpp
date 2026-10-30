// 3977. Minimum Time to Reach Target With Limited Power | 有限电量到达目标节点的最少时间（困难）
// 核心思路：把状态定义为（节点, 剩余电量），在这个扩展图上跑 Dijkstra 求最短路；优先队列按（时间, 剩余电量的相反数）排序，于是时间相同时电量更多的状态先出队，第一次弹出 target 时得到的时间与电量即答案，走不到则返回 {-1, -1}。
// 复杂度：时间 O((n + m) · power · log(n · power))，m 为边数，每个状态至多入队一次劣化版本；空间 O(n · power)，主要是 dist 表与优先队列。
class Solution {  // 定义题解类
public:  // 公有接口
    vector<long long> minTimeMaxPower(  // 返回 {最少时间, 该时间下剩余电量}，不可达时返回 {-1, -1}
        int n,  // 节点个数
        vector<vector<int>>& edges,  // 有向边列表，每条边是 {u, v, t}
        int power,  // 出发时的总电量
        vector<int>& cost,  // cost[u]：离开节点 u 需要消耗的电量
        int source,  // 起点
        int target) {  // 终点
        using ll = long long;  // 简化长整型写法，时间可能累加很大
        const ll inf = LLONG_MAX / 4;  // 无穷大，除以 4 是为了后续加法不溢出

        vector<vector<pair<int, int>>> g(n);  // 邻接表，g[u] 里存 (后继节点, 边耗时)
        for (auto& e : edges) {  // 遍历每条有向边
            g[e[0]].push_back({e[1], e[2]});  // 只建单向边，题目给的是有向图
        }  // 建图结束

        vector<vector<ll>> dist(n, vector<ll>(power + 1, inf));  // dist[u][p]：到达 u 且剩余 p 电量时的最少时间

        using T = tuple<ll, int, int>;  // 优先队列元素：{时间, -剩余电量, 节点}
        priority_queue<T, vector<T>, greater<T>> pq;  // 小根堆，先比时间，时间相同则比 -电量（即电量多者优先）

        dist[source][power] = 0;  // 起点：满电，时间 0
        pq.push({0, -power, source});  // 把起点状态入堆；电量取负是为了让 greater 按“电量从大到小”排序

        while (!pq.empty()) {  // 标准 Dijkstra 主循环
            auto [d, negp, u] = pq.top();  // 取出当前最优状态：时间 d、电量编码 negp、节点 u
            pq.pop();  // 弹出堆顶

            int p = -negp;  // 把负号还原成真实的剩余电量

            if (u == target) return {d, p};  // 第一次弹出终点即为最优：时间最少，且时间相同时电量最多
            if (d > dist[u][p] || p < cost[u]) continue;  // 懒删除过期状态；电量不足以离开 u 时该状态无法继续扩展

            p -= cost[u];  // 离开 u 要付出代价：先扣掉 cost[u]，剩下的电量才能带到后继节点

            for (auto& [v, t] : g[u]) {  // 枚举从 u 出发的每条边
                ll nd = d + t;  // 走到 v 之后的总时间

                if (nd < dist[v][p]) {  // 用扣掉电量后的剩余 p 作为新状态，发现更短时间
                    dist[v][p] = nd;  // 更新该状态的最短时间
                    pq.push({nd, -p, v});  // 新状态入堆，电量同样取负
                }  // if 结束
            }  // 邻居枚举结束
        }  // 搜索结束

        return {-1, -1};  // 堆空仍未弹出 target，说明在电量限制下不可达
    }  // 方法结束
};  // 类定义结束