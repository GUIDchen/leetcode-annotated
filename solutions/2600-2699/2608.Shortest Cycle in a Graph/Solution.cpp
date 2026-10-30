// 题目：2608. 图中的最短环（Shortest Cycle in a Graph）
// 思路：枚举每条边并临时删除它，用 BFS 求两端点之间的最短路，最短路长度 + 1 就是经过该边的环长，全部取最小。
// 时间复杂度：O(E(V + E))，每条边做一次 BFS；空间复杂度：O(V + E)，邻接表加距离数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findShortestCycle(int n, vector<vector<int>>& edges) {  // n：点数；edges：无向边表；返回最短环长度
        vector<vector<int>> g(n);  // 邻接表，g[i] 保存所有与 i 相邻的点
        for (auto& e : edges) {  // 遍历每条无向边
            int u = e[0], v = e[1];  // 拆出边的两个端点
            g[u].push_back(v);  // 建立正向边 u -> v
            g[v].push_back(u);  // 建立反向边 v -> u（无向图）
        }  // 邻接表建好
        const int inf = 1 << 30;  // 用 2^30 表示「不可达」，避免加法溢出
        auto bfs = [&](int u, int v) -> int {  // lambda：临时删掉边 (u,v)，求 u 到 v 的最短路
            int dist[n];  // dist[i]：从 u 出发到 i 的最短距离
            fill(dist, dist + n, inf);  // 全部初始化为不可达
            dist[u] = 0;  // 起点到自己的距离为 0
            queue<int> q{{u}};  // BFS 队列，先把起点 u 压入
            while (!q.empty()) {  // 队列非空就继续扩展
                int i = q.front();  // 取队首
                q.pop();  // 弹出队首
                for (int j : g[i]) {  // 遍历 i 的所有邻居
                    if ((i == u && j == v) || (i == v && j == u) || dist[j] != inf) {  // 跳过被删掉的边 (u,v)/(v,u)，以及已经访问过的点
                        continue;  // 该邻居不可用，直接看下一个
                    }  // 条件分支结束
                    dist[j] = dist[i] + 1;  // 记录从 u 走来需要 dist[i] + 1 步
                    q.push(j);  // 新到达的点入队
                }  // 邻居遍历结束
            }  // BFS 结束
            return dist[v] + 1;  // 绕开被删的边，路径长度 + 1 才是环长
        };  // lambda 定义结束
        int ans = inf;  // ans：当前找到的最短环长
        for (auto& e : edges) {  // 枚举每条边，假设它是环上被删掉的那一条
            int u = e[0], v = e[1];  // 取边的两个端点
            ans = min(ans, bfs(u, v));  // 用「删边求最短路 + 1」更新答案
        }  // 边表枚举结束
        return ans < inf ? ans : -1;  // 没找到环则返回 -1
    }  // 方法结束
};  // 类定义结束