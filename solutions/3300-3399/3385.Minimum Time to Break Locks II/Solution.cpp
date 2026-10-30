// 题目：3385. 破解锁的最少时间 II（Minimum Time to Break Locks II）
// 思路：把「第 i 把锁安排在第 j+1 个位置破解」建成二分图的最小费用最大流，边权为 ceil(strength[i] / (j+1))，跑 MCF 求满流 n 的最小费用。
// 时间复杂度：O(n^3 log n) 量级（逐条增广 + 堆优化 Dijkstra）；空间复杂度：O(n^2)，二分图最多 n^2 条边。
class MCFGraph {  // 最小费用流（MCF）模板类
public:  // 对外接口
    MCFGraph(int n)  // 构造函数：传入顶点数
        : n(n)  // 记录顶点数 n
        , g(n) {}  // 按顶点数开好 n 个空邻接表

    void addEdge(int src, int dst, int cap, int cost) {  // 加一条容量 cap、单位费用 cost 的边 src -> dst
        int i = g[src].size();  // 记录这条边在 src 出边表中的下标，供反向边回指
        int j = g[dst].size();  // 记录反向边在 dst 出边表中的下标
        g[src].push_back({dst, cap, cost, j});  // 正向边：容量 cap、费用 cost，rev 指向反向边
        g[dst].push_back({src, 0, -cost, i});  // 反向边：容量 0、费用取负，rev 指回正向边
    }

    pair<int, int> flow(int s, int t, int flowLimit) {  // 求 s 到 t、流量上限 flowLimit 的最小费用流
        return slope(s, t, flowLimit).back();  // slope 返回分段的 (流量, 费用)，最后一段即满流时的结果
    }

private:  // 以下为内部实现
    struct _Edge {  // 边结构：目标点、剩余容量、单位费用、反向边下标
        int dst, cap, cost, rev;  // 一条边的四个字段
    };

    int n;  // 顶点数
    vector<vector<_Edge>> g;  // 邻接表：g[v] 保存 v 的所有出边

    vector<pair<int, int>> slope(int s, int t, int flowLimit) {  // 返回「流量-最小费用」的分段线性函数端点
        vector<int> dual(n);  // dual：每个点的势能，使修正后的边权非负，负权也能用 Dijkstra
        vector<int> pv(n), pe(n);  // pv[w] 记录最短路树中 w 的前驱点，pe[w] 记录所用的边下标
        auto refineDual = [&]() -> bool {  // 用当前势能跑一次最短路，成功则更新势能并返回 true
            vector<int> dist(n, INT_MAX);  // dist：考虑势能修正后的距离，初始为无穷大
            vector<char> vis(n);  // vis：Dijkstra 的出队标记（惰性删除）
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;  // 小根堆，按距离从小到大取点
            dist[s] = 0;  // 起点距离为 0
            pq.emplace(0, s);  // 起点入堆
            while (!pq.empty()) {  // 堆非空就继续松弛
                auto [distV, v] = pq.top();  // 取出当前距离最小的点
                pq.pop();  // 弹出（可能取到过期条目）
                if (vis[v]) {  // 该点已经确定过最短路
                    continue;  // 跳过过期堆条目
                }
                vis[v] = 1;  // 标记为已确定
                if (v == t) {  // 到达汇点就可以提前结束
                    break;  // 提前 break，后面的点不必再松弛
                }
                int dualV = dual[v];  // 当前点的势能
                for (int i = 0; i < (int) g[v].size(); ++i) {  // 遍历 v 的所有出边
                    auto& e = g[v][i];  // 取边的引用，后面要读容量与费用
                    int w = e.dst;  // 边指向的邻居
                    if (vis[w] || e.cap == 0) {  // 邻居已确定最短路，或这条边没有剩余容量
                        continue;  // 跳过不可用的边
                    }
                    int newDist = distV + e.cost - dual[w] + dualV;  // 修正后的边权：cost + dual[v] - dual[w]，保证非负
                    if (newDist < dist[w]) {  // 能松弛就更新
                        dist[w] = newDist;  // 更新到 w 的距离
                        pv[w] = v;  // 记录前驱点
                        pe[w] = i;  // 记录前驱边下标
                        pq.emplace(newDist, w);  // 更新后的点入堆，等待继续松弛
                    }
                }
            }
            if (!vis[t]) {  // 汇点没被访问到，说明不存在增广路
                return false;  // 返回 false，结束增广
            }
            int distT = dist[t];  // 汇点的最短路
            for (int v = 0; v < n; ++v) {  // 用本次最短路更新所有已访问点的势能
                if (vis[v]) {  // 只更新被访问过的点
                    dual[v] -= distT - dist[v];  // 势能按 distT - dist[v] 下调
                }
            }
            return true;  // 成功找到一条增广路
        };

        int flow = 0, cost = 0;  // flow：当前流量；cost：当前总费用
        int prevCostPerFlow = INT_MIN;  // 上一段的单位费用，用于合并相同斜率的段
        vector<pair<int, int>> result = {{0, 0}};  // 结果从 (0, 0) 开始
        while (flow < flowLimit) {  // 流量还没到上限就继续增广
            if (!refineDual()) {  // 先更新势能并求出最短路
                break;  // 没有增广路就退出
            }
            int f = flowLimit - flow;  // 本次最多还能增广的流量
            for (int v = t; v != s; v = pv[v]) {  // 沿最短路回溯，求路径上的瓶颈容量
                f = min(f, g[pv[v]][pe[v]].cap);  // 取路径上剩余容量的最小值
            }
            for (int v = t; v != s; v = pv[v]) {  // 再沿最短路回溯一次，真正修改容量
                auto& e = g[pv[v]][pe[v]];  // 取出路径上的这条边
                e.cap -= f;  // 正向边剩余容量减少
                g[v][e.rev].cap += f;  // 反向边容量增加，允许之后退流
            }
            int c = -dual[s];  // 本段的单位费用（等于 -dual[s]）
            flow += f;  // 累加流量
            cost += f * c;  // 累加费用
            if (c == prevCostPerFlow) {  // 本段斜率与上一段相同
                result.pop_back();  // 合并：删掉上一段的端点
            }
            result.emplace_back(flow, cost);  // 记录新的 (流量, 费用) 端点
            prevCostPerFlow = c;  // 记住本段单位费用
        }
        return result;  // 返回所有分段端点
    }
};  // 最小费用流模板定义结束

class Solution {  // LeetCode 约定的题解类
public:
    int findMinimumTime(vector<int>& strength) {  // strength：每把锁的强度值，返回破解全部锁的最少总时间
        int n = strength.size();  // 锁的数量
        int s = n * 2;  // 左部 n 个点代表锁，源点编号为 2n
        int t = s + 1;  // 汇点编号为 2n + 1
        MCFGraph g(t + 1);  // 建图：一共 2n + 2 个点
        for (int i = 0; i < n; ++i) {  // 枚举每把锁
            g.addEdge(s, i, 1, 0);  // 源点 -> 锁 i：容量 1、费用 0
            g.addEdge(i + n, t, 1, 0);  // 位置 (i + n) -> 汇点：容量 1、费用 0
            for (int j = 0; j < n; ++j) {  // 枚举它被安排成第 j+1 个被破解
                g.addEdge(i, j + n, 1, (strength[i] - 1) / (j + 1) + 1);  // 匹配费用为 ceil(strength[i] / (j+1))，用整除写法避免浮点误差
            }
        }
        return g.flow(s, t, n).second;  // 满流 n 的最小费用即答案（second 是总费用）
    }
};  // 题解类定义结束
