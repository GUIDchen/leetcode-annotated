// 题目：2065. 最大化一张图中的路径价值（Maximum Path Quality of a Graph）
// 思路：DFS 枚举从 0 号点出发、总耗时不超过 maxTime 的所有路径；节点只在本次路径首次到达时累加价值，回到 0 号点就更新答案。
// 时间复杂度：O(b^maxTime)，b 为平均度数，路径数随 maxTime 指数增长；空间复杂度：O(n + E)，用于邻接表与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {  // values 是各节点价值，edges 是带耗时的边，maxTime 是允许的总耗时
        int n = values.size();  // 图的节点个数
        vector<pair<int, int>> g[n];  // 邻接表：g[u] 存 u 的邻居和这条边的耗时
        for (auto& e : edges) {  // 遍历每条无向边，建双向邻接表
            int u = e[0], v = e[1], t = e[2];  // 取出边的两个端点和耗时
            g[u].emplace_back(v, t);  // 建 u → v 方向的有向边
            g[v].emplace_back(u, t);  // 建 v → u 方向的有向边
        }
        bool vis[n];  // vis 标记节点是否在「当前这条路径」上出现过
        memset(vis, false, sizeof(vis));  // 全部初始化为未访问
        vis[0] = true;  // 起点 0 号节点一开始就在路径上
        int ans = 0;  // ans 记录所有可行路径中能拿到的最大价值
        // 递归 lambda：C++23 用 this auto&& dfs 让 lambda 内部能调用自身
        // u 是当前节点，cost 是已花时间，value 是当前累计价值
        auto dfs = [&](this auto&& dfs, int u, int cost, int value) -> void {  // 参数与返回值类型显式写出，便于自递归
            if (u == 0) {  // 回到 0 号点，说明走完了一条从 0 出发回到 0 的闭环路径
                ans = max(ans, value);  // 只在闭环处结算，保证路径的起点和终点都是 0
            }
            for (auto& [v, t] : g[u]) {  // 枚举 u 的每条出边，结构化绑定取出邻居 v 与耗时 t
                if (cost + t <= maxTime) {  // 剪枝：再走这条边也不能超过 maxTime
                    if (vis[v]) {  // 邻居已经在当前路径上出现过
                        dfs(v, cost + t, value);  // 重复访问不重复计价值，沿用当前 value 继续深搜
                    } else {  // 否则这是本路径第一次到达该节点
                        vis[v] = true;  // 先打标记，防止同一节点价值被重复累加
                        dfs(v, cost + t, value + values[v]);  // 首次到达才加上 values[v]
                        vis[v] = false;  // 回溯：撤销标记，让其它搜索分支还能把它当作新节点
                    }
                }
            }
        };  // 递归 lambda 定义结束
        dfs(0, 0, values[0]);  // 从 0 号点出发，耗时 0，初始价值就是 values[0]
        return ans;  // 返回搜索得到的最大路径价值
    }
};
