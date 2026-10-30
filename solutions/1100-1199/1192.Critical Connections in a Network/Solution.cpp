// 题目：1192. 查找集群内的关键连接（Critical Connections in a Network）
// 思路：Tarjan 求桥。DFS 时维护 dfn（首次访问时间）与 low（子树能回溯到的最小时间），若子节点满足 low[b] > dfn[a]，则 a-b 是桥。
// 时间复杂度：O(n + m)，每条边只访问常数次；空间复杂度：O(n + m)，邻接表与两个数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {  // n 个节点，connections 是无向边表，返回所有关键连接（桥）
        int now = 0;  // Tarjan 的访问时间戳计数器
        vector<int> dfn(n);  // dfn[v]：节点 v 首次被访问的时间，0 表示还没访问过
        vector<int> low(n);  // low[v]：v 及其子树通过回边能回溯到的最小 dfn
        vector<int> g[n];  // 邻接表，题目保证图连通，只需一个连通分量即可覆盖全部点
        for (auto& e : connections) {  // 遍历边表建无向图
            int a = e[0], b = e[1];  // 取出这条边的两个端点
            g[a].push_back(b);  // a 的邻居里加入 b
            g[b].push_back(a);  // b 的邻居里加入 a（无向图双向往记）
        }  // 建图结束
        vector<vector<int>> ans;  // 收集所有的桥
        function<void(int, int)> tarjan = [&](int a, int fa) -> void {  // 递归 Lambda：a 是当前节点，fa 是它的父节点
            dfn[a] = low[a] = ++now;  // 打时间戳；low 先设为自己，之后只会越取越小
            for (int b : g[a]) {  // 遍历 a 的所有邻居
                if (b == fa) {  // 跳过父节点，否则无向边会被误当成回边
                    continue;  // 处理下一个邻居
                }  // 分支结束
                if (!dfn[b]) {  // b 还没被访问过，说明 (a, b) 是 DFS 树边
                    tarjan(b, a);  // 递归深入 b
                    low[a] = min(low[a], low[b]);  // 用 b 子树能回溯到的最小时间更新 a 的 low
                    if (low[b] > dfn[a]) {  // b 的子树回不到 a 或更早的节点，说明删掉 a-b 图会断开
                        ans.push_back({a, b});  // 记录这条关键连接
                    }  // if 结束
                } else {  // b 已被访问，说明 (a, b) 是一条回边
                    low[a] = min(low[a], dfn[b]);  // 用 b 的访问时间更新 a 的 low（无向图用 dfn[b] 即可）
                }  // else 结束
            }  // 邻居遍历结束
        };  // Lambda 定义结束
        tarjan(0, -1);  // 从 0 号节点开始 DFS，父节点记为 -1
        return ans;  // ans 中就是全部桥
    }  // 方法结束
};  // 类定义结束