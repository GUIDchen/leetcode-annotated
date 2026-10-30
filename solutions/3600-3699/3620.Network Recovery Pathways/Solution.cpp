// 3620. Network Recovery Pathways（3620. 恢复网络路径）
// 核心思路：二分最终路径的“最小边权”mid，每次只保留权值 >= mid 的边，用 Dijkstra 求 0 到 n-1 的最短路并判断是否不超过 k，可行就抬高下界。
// 复杂度：二分 O(log W) 轮，每轮 Dijkstra O((n + m) log n)，总时间 O((n + m) log n log W)，空间 O(n + m)。
class Solution {  // 定义题解类
public:  // 公有成员，供判题器调用
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {  // 求在线路径分数最大值
        int n = online.size();  // 顶点个数
        vector<vector<pair<int, int>>> g(n);  // 邻接表：pair<邻接点, 边权>

        int l = INT_MAX, r = 0;  // 二分边界：可行边权的最小值与最大值

        for (auto& e : edges) {  // 遍历所有边建图
            int u = e[0], v = e[1], w = e[2];  // 两个端点 u、v 与边权 w
            if (!online[u] || !online[v]) continue;  // 任一端点离线则丢弃这条边
            g[u].push_back({v, w});  // 加入有向边 u -> v
            l = min(l, w);  // 更新下界
            r = max(r, w);  // 更新上界
        }

        auto check = [&](int mid) -> bool {  // 判定：只走边权 >= mid 的边，能否在预算 k 内到达终点
            vector<long long> dist(n, LLONG_MAX / 4);  // 最短路数组，用大值代替无穷以防溢出
            dist[0] = 0;  // 起点到自身距离为 0

            using P = pair<long long, int>;  // 堆元素类型：pair<距离, 顶点>
            priority_queue<P, vector<P>, greater<P>> pq;  // 按距离升序的小顶堆
            pq.push({0, 0});  // 起点入堆

            while (!pq.empty()) {  // 堆非空时继续扩展
                auto [d, u] = pq.top();  // 取出当前距离最小的状态
                pq.pop();  // 弹出堆顶

                if (d > k) return false;  // 累计花费已超预算，立即剪枝
                if (u == n - 1) return true;  // 已到终点且未超预算，可行
                if (dist[u] < d) continue;  // 说明是过期状态，跳过

                for (auto& ed : g[u]) {  // 遍历 u 的所有出边
                    int v = ed.first, w = ed.second;  // 邻接点与边权
                    if (w < mid) continue;  // 边权小于 mid，不允许经过

                    long long nd = d + w;  // 经过这条边后的新花费
                    if (nd < dist[v]) {  // 可以松弛
                        dist[v] = nd;  // 更新最短路
                        pq.push({nd, v});  // 新状态入堆
                    }
                }
            }
            return false;  // 无法在预算内到达终点
        };

        while (l < r) {  // 二分最短路边权的最大可行值
            int mid = (l + r + 1) >> 1;  // 取上中位数，与 l = mid 配合避免死循环
            if (check(mid))  // mid 可行，答案不小于 mid
                l = mid;  // 抬高下界
            else  // mid 不可行，答案更小
                r = mid - 1;  // 降低上界
        }

        return check(l) ? l : -1;  // 再验证一次最终答案，不可达则返回 -1
    }
};