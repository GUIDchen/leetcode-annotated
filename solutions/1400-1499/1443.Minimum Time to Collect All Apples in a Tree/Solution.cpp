// 题目：1443. 收集树上所有苹果的最少时间（Minimum Time to Collect All Apples in a Tree）
// 思路：以 0 为根做后序 DFS，返回该子树需要走的边数；子树内没有苹果的分支完全不必进入。
// 时间复杂度：O(n)，每个节点与每条边各访问一次；空间复杂度：O(n)，邻接表与访问标记。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {  // n 是节点数，edges 是无向边，hasApple 标记哪些节点有苹果
        vector<bool> vis(n);  // 访问标记；树被存成无向图后需要防止走回父节点
        vector<vector<int>> g(n);  // 邻接表，g[u] 保存与 u 相邻的所有节点
        for (auto& e : edges) {  // 逐条边建图
            int u = e[0], v = e[1];  // 这条边连接的两个端点
            g[u].push_back(v);  // 无向边：u 的邻居里加上 v
            g[v].push_back(u);  // 无向边：v 的邻居里加上 u
        }
        return dfs(0, 0, g, hasApple, vis);  // 从根节点 0 出发；根自身没有入边，所以初始代价为 0
    }

    int dfs(int u, int cost, vector<vector<int>>& g, vector<bool>& hasApple, vector<bool>& vis) {  // u 是当前节点，cost 是进入这一分支的代价（根为 0，其它为 2）
        if (vis[u]) return 0;  // 已访问过说明是走回了父节点，不再产生代价
        vis[u] = true;  // 标记当前节点已访问
        int nxt = 0;  // nxt 累计子树中需要走的路程
        for (int& v : g[u]) nxt += dfs(v, 2, g, hasApple, vis);  // 向下的每条边都要走来回，因此子调用代价传 2
        if (!hasApple[u] && !nxt) return 0;  // 自己和子树都没有苹果，这条分支根本不用来
        return cost + nxt;  // 需要来一趟：进入代价加上子树内部路程
    }
};
