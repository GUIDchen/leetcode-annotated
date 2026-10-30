// 题目：1514. 概率最大的路径（Path with Maximum Probability）
// 思路：把概率相乘视为「边权求和」的对偶，用最大堆跑 Dijkstra 变体，按概率从大到小贪心松弛出最大概率路径。
// 时间复杂度：O((V+E) log V)，每条边最多入堆一次；空间复杂度：O(V+E)，邻接表 + dist 数组 + 堆。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {  // n：节点数；edges/succProb：无向边及对应成功概率；start_node/end_node：起终点
        using pdi = pair<double, int>;  // 堆元素类型别名：first 是概率（越大越优先），second 是节点编号
        vector<pdi> g[n];  // 邻接表：g[a] 存放所有 (边概率, 邻居 b)
        for (int i = 0; i < edges.size(); ++i) {  // 遍历每条边，把无向边拆成两个方向
            int a = edges[i][0], b = edges[i][1];  // a、b：这条边的两个端点
            double p = succProb[i];  // p：这条边通行成功的概率
            g[a].emplace_back(p, b);  // 正向边 a -> b
            g[b].emplace_back(p, a);  // 反向边 b -> a（无向图）
        }  // 结束建图
        vector<double> dist(n);  // dist[v]：起点到 v 的最大概率，默认 0 表示暂不可达
        dist[start_node] = 1;  // 起点到自己的概率为 1
        priority_queue<pdi> pq;  // 大顶堆：pair 先比 first，概率大的先出堆
        pq.emplace(1, start_node);  // 起点作为初始状态入堆
        while (!pq.empty()) {  // 堆非空说明还有可松弛的状态
            auto [w, a] = pq.top();  // 取出当前概率最大的状态并结构化解包
            pq.pop();  // 弹出堆顶
            if (dist[a] > w) {  // 堆里存的是历史快照，w 小于已知最优值说明是过期条目
                continue;  // 过期条目直接跳过
            }  // 结束过期判断
            for (auto [p, b] : g[a]) {  // 枚举 a 的所有邻边
                auto nw = w * p;  // 概率相乘得到经过这条边到达 b 的新概率
                if (nw > dist[b]) {  // 只有更优才松弛，保证 dist 单调递增
                    dist[b] = nw;  // 更新到 b 的最大概率
                    pq.emplace(nw, b);  // 把更优状态压入堆，供后续继续扩展
                }  // 结束松弛判断
            }  // 结束邻边枚举
        }  // 结束主循环
        return dist[end_node];  // 返回终点的最大概率，不可达时自然为 0
    }  // 结束方法
};  // 结束题解类
