// 题目：1334. 阈值距离内邻居最少的城市（Find the City With the Smallest Number of Neighbors at a Threshold Distance）
// 思路：把边表建成邻接矩阵，对每个城市跑一次朴素 Dijkstra，统计距离不超过阈值的城市个数；从大到小枚举城市，只在严格更小时更新，从而并列时保留编号更大的城市。
// 时间复杂度：O(n^3)，每个源点一次 O(n^2) 的 Dijkstra；空间复杂度：O(n^2)，主要是邻接矩阵。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {  // n 是城市数，edges 是 [u, v, w] 边表，distanceThreshold 是距离阈值
        int g[n][n];  // 邻接矩阵：g[i][j] 表示 i 到 j 的边权，0x3f 表示不可达
        int dist[n];  // 单源最短路距离数组，每个源点复用
        bool vis[n];  // 访问标记：该点最短路是否已确定
        memset(g, 0x3f, sizeof(g));  // 全部初始化为 0x3f3f3f3f（看作无穷大），表示初始都不可达
        for (auto& e : edges) {  // 把边表写成邻接矩阵
            int f = e[0], t = e[1], w = e[2];  // 拆出起点 f、终点 t、权重 w
            g[f][t] = g[t][f] = w;  // 无向边，两个方向都要赋值
        }  // 建图结束
        auto dijkstra = [&](int u) {  // 以 u 为源点跑 Dijkstra，返回距离不超过阈值的城市数量（含自身）
            memset(dist, 0x3f, sizeof(dist));  // 距离重置为无穷大
            memset(vis, 0, sizeof(vis));  // 访问标记全部重置为未访问
            dist[u] = 0;  // 源点到自身距离为 0
            for (int i = 0; i < n; ++i) {  // 共 n 轮，每轮确定一个点的最短路
                int k = -1;  // 本轮要选出的、当前距离最小的未访问点，-1 表示还没选到
                for (int j = 0; j < n; ++j) {  // 在全部未访问点里找距离最小的
                    if (!vis[j] && (k == -1 || dist[j] < dist[k])) {  // k == -1 表示这是第一个候选点，直接取；否则比较距离
                        k = j;  // 更新最优候选点
                    }  // 内层枚举结束
                }  // 选点结束
                vis[k] = true;  // 把 k 标记为最短路已确定
                for (int j = 0; j < n; ++j) {  // 用 k 作为中转去松弛其它所有点
                    dist[j] = min(dist[j], dist[k] + g[k][j]);  // 松弛：经由 k 走更短就更新 dist[j]
                }  // 松弛结束
            }  // 一轮结束
            return count_if(dist, dist + n, [&](int d) { return d <= distanceThreshold; });  // 统计 dist ≤ 阈值的城市个数（包含自身距离 0，对所有城市都多算 1，不影响比较）
        };  // lambda 结束
        int ans = n, cnt = n + 1;  // ans 记录答案城市，cnt 记录当前最少的邻居数（初始为不可能的大值）
        for (int i = n - 1; ~i; --i) {  // 从编号大到小枚举：邻居数相同时不再更新，从而保留编号更大的城市
            int t = dijkstra(i);  // 计算城市 i 的邻居数量
            if (t < cnt) {  // 严格更少才更新，保证并列时取编号更大者
                cnt = t;  // 更新最少邻居数
                ans = i;  // 更新答案城市
            }  // 条件分支结束
        }  // 枚举结束
        return ans;  // 返回邻居最少且编号最大的城市
    }  // 方法结束
};  // 类定义结束