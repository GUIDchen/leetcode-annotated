// 题目：743. 网络延迟时间（Network Delay Time）
// 核心思路：Dijkstra 单源最短路（邻接矩阵 + 每轮线性挑最近的未访问点），求出信号从 k 传到所有节点的最短时间并取最大值；仍有不可达节点则返回 -1。
// 时间复杂度：O(n^2 + m)，n 轮各做两次 O(n) 扫描；空间复杂度：O(n^2)，邻接矩阵与距离数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {  // times：有向边 (u, v, w)；n：节点数；k：信号源节点（编号从 1 开始）
        const int inf = 1 << 29;  // 用一个足够大的数表示「不可达」，远大于任何合法边权之和，避免被误当成真距离
        vector<vector<int>> g(n, vector<int>(n, inf));  // 邻接矩阵：g[u][v] 存 u→v 的边权，先全部视为不可达
        for (const auto& e : times) {  // 遍历每条有向边，把边权写进矩阵
            g[e[0] - 1][e[1] - 1] = e[2];  // 题目节点编号从 1 开始，这里转成 0 起始的矩阵下标
        }  // 结束边读入
        vector<int> dist(n, inf);  // dist[i]：源点到节点 i 的最短距离，初始都设为不可达
        dist[k - 1] = 0;  // 源点到自己的距离是 0，同样把 1 起始编号转成 0 起始下标
        vector<bool> vis(n);  // vis[i] 标记节点 i 的最短路是否已经最终确定，vector<bool> 默认全为 false
        for (int i = 0; i < n; ++i) {  // 最多 n 轮，每轮确定一个最近未访问节点
            int t = -1;  // t 是本轮选中的节点，-1 表示还没有候选
            for (int j = 0; j < n; ++j) {  // 线性扫描所有节点，找 dist 最小的未访问点
                if (!vis[j] && (t == -1 || dist[t] > dist[j])) {  // j 未访问且比当前候选更近（t == -1 时无条件接受第一个候选）
                    t = j;  // 把本轮候选更新为 j
                }  // 结束候选比较
            }  // 结束线性扫描
            vis[t] = true;  // 选中点 t 的最短路已经确定，打上访问标记
            for (int j = 0; j < n; ++j) {  // 用 t 去松弛它的所有出边
                dist[j] = min(dist[j], dist[t] + g[t][j]);  // 经 t 中转更短就更新；不可达时加出来仍是超大数，不会错误地变优
            }  // 结束松弛
        }  // 结束 n 轮 Dijkstra 主循环
        int ans = ranges::max(dist);  // 所有节点都收到信号的时间，就是所有最短路里的最大值
        return ans == inf ? -1 : ans;  // 最大值仍等于初始不可达值，说明有节点收不到信号，按题意返回 -1
    }  // 结束 networkDelayTime 方法
};  // 结束 Solution 类
