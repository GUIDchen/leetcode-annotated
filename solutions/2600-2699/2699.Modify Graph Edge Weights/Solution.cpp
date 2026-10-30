// 题目：2699. 修改图中的边权（Modify Graph Edge Weights）
// 核心思路：先把权值为 -1 的边视为不存在求最短路。若已知边已让最短路小于 target 则无解；否则按顺序把每条待定边先设成 1 再求最短路，一旦最短路不超过 target，就把这条边加长「target - d」，使最短路恰好等于 target，之后剩余待定边全部设成无穷大。
// 时间复杂度：O(m * (n^2 + m))，m 为边数，每次修改一条待定边就要跑一遍 O(n^2+m) 的朴素 Dijkstra；空间复杂度：O(n^2)，邻接矩阵。
using ll = long long;  // 用 ll 简写 64 位整数，避免边权累加时溢出
const int inf = 2e9;  // 无穷大：2e9 大于任何合法边权，距离相加仍在 long long 范围内

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {  // n：结点数；edges：边表（权值为 -1 表示可修改）；source/destination：起点终点；target：要求的最短距离
        ll d = dijkstra(edges, n, source, destination);  // 先只考虑已知权重的边求最短路（-1 边当作不存在）
        if (d < target) {  // 已知边已经把最短路压得比 target 还小，而边权只能变大或不变，故无解
            return {};  // 返回空数组表示无解
        }
        bool ok = d == target;  // 若已知边的最短路恰好等于 target，则待定边只需设成极大的数，不参与最短路
        for (auto& e : edges) {  // 按顺序逐条处理边
            if (e[2] > 0) {  // 权值已经确定的边不允许修改
                continue;  // 跳过这条边
            }
            if (ok) {  // 最短路已经等于 target，剩下的待定边不能再来缩短它
                e[2] = inf;  // 设成无穷大，等价于这条边不参与任何最短路
                continue;  // 处理下一条
            }
            e[2] = 1;  // 先试探性地把这条待定边设成最小合法权值 1
            d = dijkstra(edges, n, source, destination);  // 边权变了，重新跑一遍最短路
            if (d <= target) {  // 说明这条边落在了某条长度不超过 target 的最短路上
                ok = true;  // 最短路已锁定，后面的待定边都可以设成无穷大
                e[2] += target - d;  // 把这条边加长 target - d，使最短路恰好等于 target
            }
        }
        return ok ? edges : vector<vector<int>>{};  // 能把最短路凑成 target 才返回修改后的边表，否则返回空数组
    }

    // 朴素 O(n^2) Dijkstra：返回 src 到 dest 的最短距离，权重为 -1 的边视为不存在
    ll dijkstra(vector<vector<int>>& edges, int n, int src, int dest) {  // edges：当前边表；n：结点数；src：起点；dest：终点
        ll g[n][n];  // 邻接矩阵（变长数组），g[a][b] 表示 a→b 的边权
        ll dist[n];  // dist[i]：src 到 i 的当前最短距离
        bool vis[n];  // vis[i]：i 的最短距离是否已经确定
        for (int i = 0; i < n; ++i) {  // 初始化这三份数组
            fill(g[i], g[i] + n, inf);  // 邻接矩阵第 i 行全部置为无穷大，表示暂时没有边
            dist[i] = inf;  // 距离初值全为无穷大
            vis[i] = false;  // 所有点一开始都未确定
        }
        dist[src] = 0;  // 源点到自身的距离为 0
        for (auto& e : edges) {  // 把已有权重的边写入邻接矩阵
            int a = e[0], b = e[1], w = e[2];  // e 的三个元素分别是端点 a、b 与权值 w
            if (w == -1) {  // 权值为 -1 的待定边当前还不能用
                continue;  // 直接忽略，相当于这条边不存在
            }
            g[a][b] = w;  // 无向图，a → b 连通
            g[b][a] = w;  // 无向图，b → a 连通
        }
        for (int i = 0; i < n; ++i) {  // 一共要确定 n 个点的最短距离
            int k = -1;  // k：本轮被选中的、距离最小的未确定点，-1 表示还没选
            for (int j = 0; j < n; ++j) {  // 在尚未确定的点里找 dist 最小的那个
                if (!vis[j] && (k == -1 || dist[j] < dist[k])) {  // k == -1 时无条件赋值，否则与当前最优比较
                    k = j;  // 记录本轮候选点
                }
            }
            vis[k] = true;  // 该点的最短距离就此确定
            for (int j = 0; j < n; ++j) {  // 用 k 去松弛所有点
                dist[j] = min(dist[j], dist[k] + g[k][j]);  // 松弛：直接走 k 是否比原来的路径更短
            }
        }
        return dist[dest];  // src → dest 的最短距离，不可达时返回 inf
    }
};