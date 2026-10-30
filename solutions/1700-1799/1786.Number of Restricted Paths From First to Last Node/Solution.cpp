// 题目：1786. 从第一个节点出发到最后一个节点的受限路径数（Number of Restricted Paths From First to Last Node）
// 思路：先用 Dijkstra 以终点 n 为源求出每个点到 n 的最短距离 dist，再在满足 dist 严格递减的有向关系上做记忆化 DFS 统计方案数。
// 时间复杂度：O((n + m) log n)，堆优化 Dijkstra 加一次记忆化搜索；空间复杂度：O(n + m)，邻接表、dist、f 与堆。
using pii = pair<int, int>;  // 类型别名：pii 表示二元组 (距离或权值, 节点编号)，省去反复书写模板参数

class Solution {  // LeetCode 约定的题解类
public:  // 以下成员对外可见，判题器只调用 countRestrictedPaths
    const int inf = INT_MAX;  // 无穷大常量：表示「暂时不可达」，用 INT_MAX 便于初始化与比较
    const int mod = 1e9 + 7;  // 取模常量 1e9+7：路径数可能极大，每步累加后都要取余
    vector<vector<pii>> g;  // 邻接表：g[u] 保存 u 的所有出边 (邻居, 边权)
    vector<int> dist;  // dist[x]：节点 x 到终点 n 的最短距离，由 Dijkstra 求出
    vector<int> f;  // 记忆化数组 f：f[i] 保存从 i 出发的受限路径数，-1 表示尚未计算
    int n;  // 成员变量保存节点总数，方便 dfs 判断是否到达终点

    int countRestrictedPaths(int n, vector<vector<int>>& edges) {  // 主函数：返回从节点 1 到节点 n 的受限路径条数（要求沿途 dist 严格递减）
        this->n = n;  // 把参数 n 存入成员变量，避免 dfs 递归时还要额外传参
        g.resize(n + 1);  // 邻接表开到 n+1 个槽位：节点编号 1..n，下标 0 空置不用
        dist.assign(n + 1, inf);  // dist 全部初始化为无穷大，表示初始时都不可达
        f.assign(n + 1, -1);  // f 全部初始化为 -1，表示「该状态还没有被计算过」
        dist[n] = 0;  // 终点到自身的距离为 0，作为 Dijkstra 的起点
        for (auto& e : edges) {  // 遍历每条无向边，按邻接表建图
            int u = e[0], v = e[1], w = e[2];  // 拆出这条边的两个端点 u、v 以及边权 w
            g[u].emplace_back(v, w);  // 正向边：u 到 v 有一条权值为 w 的边
            g[v].emplace_back(u, w);  // 反向边：无向图所以 v 到 u 也要加一条相同的边
        }
        priority_queue<pii, vector<pii>, greater<pii>> q;  // 小根堆：按 (距离, 节点) 字典序取最小，用于堆优化 Dijkstra
        q.emplace(0, n);  // 起点设为终点 n、初始距离 0（反向思考：求每个点到 n 的最短距离）
        while (!q.empty()) {  // 堆非空说明还有可以继续松弛的点
            auto [_, u] = q.top();  // 取出堆顶；下划线表示丢弃距离值，只关心节点编号
            q.pop();  // 弹出堆顶状态，表示已经用它完成一次松弛
            for (auto [v, w] : g[u]) {  // 遍历 u 的每个邻居 v 以及对应的边权 w
                if (dist[v] > dist[u] + w) {  // 松弛条件：经由 u 走到 v 比已知距离更短时才更新
                    dist[v] = dist[u] + w;  // 更新 v 到终点的最短距离
                    q.emplace(dist[v], v);  // 把更新后的 (距离, 节点) 入堆，等待它继续向外扩散
                }
            }
        }
        return dfs(1);  // 从节点 1 出发做记忆化搜索，统计受限路径总数
    }

    int dfs(int i) {  // dfs(i)：返回从 i 出发、每一步 dist 严格减小的路径条数
        if (f[i] != -1) return f[i];  // 已经算过就直接返回缓存，避免重复搜索（记忆化核心）
        if (i == n) return 1;  // 到达终点说明这条路径合法结束，计作 1 条
        int ans = 0;  // 累加器：统计从 i 出发所有合法后继产生的方案数
        for (auto [j, _] : g[i]) {  // 遍历 i 的每个邻居 j，边权本步用不到，用下划线占位
            if (dist[i] > dist[j]) {  // 受限条件：下一跳必须离终点更近，即 dist 严格递减
                ans = (ans + dfs(j)) % mod;  // 累加子问题的方案数，并立即取模防止溢出
            }
        }
        f[i] = ans;  // 记忆化：把结果写回 f[i]，后续再访问即 O(1)
        return ans;  // 返回从 i 出发的受限路径数
    }
};  // 题解类定义结束
