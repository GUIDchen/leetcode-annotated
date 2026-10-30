// 题目：1976. 到达目的地的方案数（Number of Ways to Arrive at Destination）
// 思路：Dijkstra 求最短路，同时用 f 数组记录方案数：松弛出更短距离时覆盖，距离相等时累加，最后输出终点方案数。
// 时间复杂度：O(n^2)，邻接矩阵配线性找最小点；空间复杂度：O(n^2)，主要开销是邻接矩阵。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countPaths(int n, vector<vector<int>>& roads) {  // n：节点数；roads 中每条边形如 [u, v, t]，返回 0 到 n-1 的最短路条数
        const long long inf = LLONG_MAX / 2;  // 用大数充当「无穷」，除以 2 是为了后面相加时不会溢出
        const int mod = 1e9 + 7;  // 方案数需要取模的模数

        vector<vector<long long>> g(n, vector<long long>(n, inf));  // 邻接矩阵 g：g[i][j] 是 i 到 j 的边权，没有直接边时是 inf
        for (auto& e : g) {  // 初始化：逐行把矩阵填满 inf
            fill(e.begin(), e.end(), inf);  // 当前行全部置为 inf（无边的默认值）
        }  // 一行填充完毕

        for (auto& r : roads) {  // 读入每条无向道路
            int u = r[0], v = r[1], t = r[2];  // u、v 是道路两端，t 是走这条路的耗时
            g[u][v] = t;  // 无向图，两个方向都要存
            g[v][u] = t;  // 反向边
        }  // 边读完

        g[0][0] = 0;  // 起点到它自己的距离为 0，保证它第一个被定型

        vector<long long> dist(n, inf);  // dist[i]：0 号点到 i 号点的最短路长度
        fill(dist.begin(), dist.end(), inf);  // 初始化：除起点外都认为不可达
        dist[0] = 0;  // 起点距离为 0

        vector<long long> f(n);  // f[i]：0 号点到 i 号点的最短路条数
        f[0] = 1;  // 起点到自身算作 1 条（空的路径）

        vector<bool> vis(n);  // vis[i]：i 号点的最短路是否已经确定（Dijkstra 的已定型集合）
        for (int i = 0; i < n; ++i) {  // 每轮定型一个点，共 n 轮
            int t = -1;  // t 存本轮 dist 最小的未定点，-1 表示尚未找到
            for (int j = 0; j < n; ++j) {  // 线性扫描所有未定型的点
                if (!vis[j] && (t == -1 || dist[j] < dist[t])) {  // 该点未定型，并且比当前候选更近
                    t = j;  // 更新候选点
                }  // 内层扫描结束
            }  // 选点结束
            vis[t] = true;  // t 的最短路已经确定，加入已定型集合
            for (int j = 0; j < n; ++j) {  // 用刚定型的 t 去松弛其余所有点
                if (j == t) {  // 自己松弛自己没有意义
                    continue;  // 直接跳过
                }  // 若走 t 到 j 的边
                long long ne = dist[t] + g[t][j];  // 经 t 中转到 j 的候选距离
                if (dist[j] > ne) {  // 候选距离更短，说明找到了更好的路
                    dist[j] = ne;  // 更新最短距离
                    f[j] = f[t];  // 旧方案全部作废，直接继承 t 的方案数
                } else if (dist[j] == ne) {  // 距离恰好相等，说明多出了一种同样短的走法
                    f[j] = (f[j] + f[t]) % mod;  // 把 t 的方案数累加进来并取模
                }  // 松弛分支结束
            }  // 松弛循环结束
        }  // n 轮定型结束
        return (int) f[n - 1];  // 返回 0 到 n-1 的最短路条数（强转成 int 满足签名）
    }  // 方法结束
};  // 类定义结束