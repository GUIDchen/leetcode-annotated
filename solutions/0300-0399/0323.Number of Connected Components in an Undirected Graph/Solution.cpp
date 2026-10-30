// 题目：323. 无向图中连通分量的数目（Number of Connected Components in an Undirected Graph）
// 思路：按边建无向邻接表，再从每个未访问节点出发做一次 DFS，能新起一次搜索就说明多了一个连通分量。
// 时间复杂度：O(n + e)，n 为节点数、e 为边数；空间复杂度：O(n + e)，邻接表与访问标记。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countComponents(int n, vector<vector<int>>& edges) {  // n：节点数；edges：无向边列表；返回连通分量的个数
        vector<int> g[n];  // 邻接表：g[u] 存放与 u 直接相连的所有节点
        for (auto& e : edges) {  // 遍历每条无向边，把它拆成两条有向边存进邻接表
            int a = e[0], b = e[1];  // 取出边的两个端点
            g[a].push_back(b);  // a → b 这一方向
            g[b].push_back(a);  // b → a 这一方向
        }  // 建图结束
        vector<bool> vis(n);  // 访问标记数组，防止重复进入同一节点
        function<int(int)> dfs = [&](int i) {  // dfs 返回 1 表示这里发现了一个新的连通分量，返回 0 表示节点已访问过
            if (vis[i]) {  // 该节点已经被访问过
                return 0;  // 不是新分量，贡献 0
            }  // 分支结束
            vis[i] = true;  // 标记为已访问
            for (int j : g[i]) {  // 沿着邻边继续搜遍整个连通块
                dfs(j);  // 递归访问邻居
            }  // 邻居遍历结束
            return 1;  // 本次调用新覆盖了一个分量，贡献 1
        };  // dfs 定义结束
        int ans = 0;  // 统计连通分量个数
        for (int i = 0; i < n; ++i) {  // 依次以每个节点为起点尝试搜索
            ans += dfs(i);  // 新分量才会计入 1，已访问过则加 0
        }  // 起点枚举结束
        return ans;  // 返回连通分量总数
    }  // 方法结束
};  // 类定义结束
