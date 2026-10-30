// 4004. 使循环数组余额非负的最少移动次数 II / Minimum Moves to Balance Circular Array II（困难）
// 核心思路：每次操作把 1 单位余额转移给相邻的人，等价于沿环上的相邻边运输 1 单位、代价 1；于是建最小费用最大流——源点连正余额（容量=余额、费用 0），负余额连汇点（容量=缺口、费用 0），环上相邻两人之间连双向边（容量无穷、费用 1），把缺口总量送到汇点的最小费用就是最少操作次数。
// 复杂度：节点与边均为 O(n)；时间按增广轮数计（每轮 SPFA 在 O(n) 的环图上运行），空间 O(n)。
class MinCostMaxFlow {  // 最小费用最大流模板类
public:  // 公有接口
    struct Edge {  // 边结构
        int to, cap, cost, rev;  // 终点、剩余容量、单位费用、反向边在邻接表中的下标

        Edge(int to, int cap, int cost, int rev)  // 构造函数
            : to(to)  // 初始化终点
            , cap(cap)  // 初始化容量
            , cost(cost)  // 初始化费用
            , rev(rev) {}  // 初始化反向边下标
    };  // 边结构结束

    static constexpr int INF = 1e9;  // 代表无穷大的常量

    int n;  // 节点数
    vector<vector<Edge>> graph;  // 邻接表：graph[u] 存放从 u 出发的所有边

    MinCostMaxFlow(int n)  // 构造函数
        : n(n)  // 初始化节点数
        , graph(n) {}  // 按节点数分配邻接表

    void addEdge(int u, int v, int cap, int cost) {  // 加入一条 u→v 的边以及它的反向边
        graph[u].emplace_back(v, cap, cost, graph[v].size());  // 正向边，其反向边指向 v 当前边表末尾
        graph[v].emplace_back(u, 0, -cost, graph[u].size() - 1);  // 反向边容量为 0、费用取负，指回刚加入的正向边
    }  // 方法结束

    long long minCostFlow(int source, int sink, int maxFlow) {  // 从 source 到 sink 送 maxFlow 单位流量，返回最小总费用
        long long totalCost = 0;  // 累计总费用
        int currentFlow = 0;  // 已经送出的流量

        while (currentFlow < maxFlow) {  // 每次沿当前残量网络的最短路增广，直到送满
            vector<int> dist(n, INF);  // 本轮最短路距离
            vector<int> parentNode(n, -1);  // 最短路上的前驱节点
            vector<int> parentEdge(n, -1);  // 最短路上的前驱边下标
            vector<bool> inQueue(n, false);  // 节点是否在队列中，SPFA 用

            queue<int> q;  // SPFA 使用的队列
            q.push(source);  // 源点入队
            dist[source] = 0;  // 源点距离为 0
            inQueue[source] = true;  // 标记源点在队列中

            while (!q.empty()) {  // SPFA 求当前残量网络上的最短路
                int u = q.front();  // 取队首节点
                q.pop();  // 出队
                inQueue[u] = false;  // 清除入队标记

                for (int i = 0; i < graph[u].size(); i++) {  // 枚举 u 的所有出边
                    Edge& e = graph[u][i];  // 当前边
                    if (e.cap > 0 && dist[e.to] > dist[u] + e.cost) {  // 仍有剩余容量且可以松弛
                        dist[e.to] = dist[u] + e.cost;  // 更新最短距离
                        parentNode[e.to] = u;  // 记录前驱节点
                        parentEdge[e.to] = i;  // 记录前驱边下标

                        if (!inQueue[e.to]) {  // 目标点不在队列中
                            inQueue[e.to] = true;  // 标记入队
                            q.push(e.to);  // 入队继续松弛
                        }  // if 结束
                    }  // if 结束
                }  // for 结束
            }  // while 结束

            if (dist[sink] == INF) {  // 汇点不可达，说明缺口无法全部补齐
                return -1;  // 返回 -1 表示无解
            }  // if 结束

            int pushFlow = maxFlow - currentFlow;  // 本轮最多能增广的流量

            for (int cur = sink; cur != source; cur = parentNode[cur]) {  // 沿最短路从汇点回溯到源点
                Edge& e = graph[parentNode[cur]][parentEdge[cur]];  // 回溯路径上的边
                pushFlow = min(pushFlow, e.cap);  // 可增广流量受路径上最小剩余容量限制
            }  // for 结束

            for (int cur = sink; cur != source; cur = parentNode[cur]) {  // 再次沿路径回溯，实际修改流量
                Edge& e = graph[parentNode[cur]][parentEdge[cur]];  // 回溯路径上的边
                e.cap -= pushFlow;  // 正向边剩余容量减少
                graph[cur][e.rev].cap += pushFlow;  // 反向边剩余容量增加
            }  // for 结束

            currentFlow += pushFlow;  // 累加已送出的流量
            totalCost += 1LL * pushFlow * dist[sink];  // 按单位最短路费用累计总费用
        }  // while 结束

        return totalCost;  // 返回最小总费用
    }  // 方法结束
};  // 模板类结束

class Solution {  // 题解类
public:  // 公有接口
    long long minMoves(vector<int>& balance) {  // 返回使每个人余额都非负所需的最少操作次数
        int totalBalance = accumulate(balance.begin(), balance.end(), 0);  // 所有人余额之和
        if (totalBalance < 0) {  // 总余额为负，怎么搬都补不平
            return -1;  // 返回 -1 表示无法做到
        }  // if 结束

        int totalDeficit = 0;  // 缺口总量
        for (int x : balance) {  // 遍历每个人的余额
            if (x < 0) {  // 负余额需要被别人补足
                totalDeficit += -x;  // 累加缺口
            }  // if 结束
        }  // for 结束

        if (totalDeficit == 0) {  // 本来就没有缺口
            return 0;  // 无需任何操作
        }  // if 结束

        int n = balance.size();  // 人数，也就是环长
        int source = n;  // 源点编号
        int sink = n + 1;  // 汇点编号

        MinCostMaxFlow mcmf(n + 2);  // 建图：n 个位置 + 源点 + 汇点

        for (int i = 0; i < n; i++) {  // 为每个位置建边
            if (balance[i] > 0) {  // 有盈余的位置
                mcmf.addEdge(source, i, balance[i], 0);  // 源点向它提供 balance[i] 单位流量，费用 0
            } else if (balance[i] < 0) {  // 有缺口的位置
                mcmf.addEdge(i, sink, -balance[i], 0);  // 它需要 -balance[i] 单位流量，费用 0
            }  // if 结束

            mcmf.addEdge(i, (i + 1) % n, MinCostMaxFlow::INF, 1);  // 向右相邻转移 1 单位余额，代价 1
            mcmf.addEdge(i, (i - 1 + n) % n, MinCostMaxFlow::INF, 1);  // 向左相邻转移 1 单位余额，代价 1
        }  // for 结束

        return mcmf.minCostFlow(source, sink, totalDeficit);  // 送满全部缺口时的最小费用就是最少操作次数
    }  // 方法结束
};  // 类定义结束