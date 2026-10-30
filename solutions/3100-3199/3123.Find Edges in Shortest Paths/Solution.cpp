// 题目：3123. 最短路径中的边（Find Edges in Shortest Paths）
// 思路：先以 0 为源点跑 Dijkstra 求出到各点的最短路，再从终点 n-1 反向 BFS，把满足 dist[a] == dist[b] + w 的边标记为答案。
// 时间复杂度：O(m log n)，m 为边数、n 为点数；空间复杂度：O(n + m)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {  // 返回长度为 m 的数组，标记每条边是否可能出现在某条 0 -> n-1 的最短路上
        vector<vector<array<int, 3>>> g(n);  // 邻接表：每条边记录 (邻点, 边权, 边编号)
        int m = edges.size();  // m 是边数
        for (int i = 0; i < m; ++i) {  // 建图：无向边要双向加入
            auto e = edges[i];  // 取出第 i 条边的三元组 [a, b, w]
            int a = e[0], b = e[1], w = e[2];  // a、b 是端点，w 是边权
            g[a].push_back({b, w, i});  // a -> b 的记录，带上边编号 i
            g[b].push_back({a, w, i});  // b -> a 的反向记录
        }  // 结束建图
        const long long inf = (long long) 1e18;  // 用一个足够大的数表示「不可达」
        vector<long long> dist(n, inf);  // dist[x]：从 0 号点到 x 号点的最短距离
        dist[0] = 0;  // 起点到自己的距离为 0

        using pii = pair<long long, int>;  // 优先队列元素类型：(当前距离, 结点编号)
        priority_queue<pii, vector<pii>, greater<pii>> pq;  // 小根堆，每次弹出距离最小的结点
        pq.push({0, 0});  // 起点入堆

        while (!pq.empty()) {  // Dijkstra 主循环
            auto [da, a] = pq.top();  // 取出当前距离最小的 (距离, 结点)
            pq.pop();  // 弹出堆顶
            if (da > dist[a]) {  // 过期条目：该结点已存在更短的路径
                continue;  // 直接跳过这条无效记录
            }  // 结束过期判断

            for (auto [b, w, _] : g[a]) {  // 松弛 a 的所有出边（边编号这里用不到，用 _ 忽略）
                if (dist[b] > dist[a] + w) {  // 发现一条更短的路径
                    dist[b] = dist[a] + w;  // 更新到 b 的最短距离
                    pq.push({dist[b], b});  // 把新的距离入堆，供后续松弛
                }  // 结束 if (dist[b] > dist[a] + w)
            }  // 结束出边遍历
        }  // 结束 Dijkstra 主循环
        vector<bool> ans(m);  // 答案数组，默认全部为 false
        if (dist[n - 1] == inf) {  // 终点不可达，说明不存在任何最短路
            return ans;  // 直接返回全 false
        }  // 结束不可达判断
        queue<int> q{{n - 1}};  // 从终点出发反向 BFS
        while (!q.empty()) {  // BFS 主循环
            int a = q.front();  // 取出队首结点
            q.pop();  // 弹出队首
            for (auto [b, w, i] : g[a]) {  // 枚举 a 的邻边（i 是边编号）
                if (dist[a] == dist[b] + w) {  // 反向走这条边距离不变，说明它位于最短路上
                    ans[i] = true;  // 标记这条边的编号为答案
                    q.push(b);  // 继续从 b 反向扩展
                }  // 结束 if (dist[a] == dist[b] + w)
            }  // 结束邻边遍历
        }  // 结束 BFS 主循环
        return ans;  // 返回标记结果
    }  // 结束 findAnswer 方法
};  // 结束 Solution 类