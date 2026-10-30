// 题目：2316. 统计无向图中无法互相到达点对数（Count Unreachable Pairs of Nodes in an Undirected Graph）
// 思路：并查集思想用 DFS 实现——先求出每个连通块的大小 t，再用前缀思想计数：当前块里每个点与之前所有块里的点都无法互相到达，一次贡献 s*t（s 是之前块的点数之和），最后累加。
// 时间复杂度：O(n + m)，每个点与每条边只访问一次（m 为边数）；空间复杂度：O(n + m)，邻接表与访问数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countPairs(int n, vector<vector<int>>& edges) {  // n：节点数；edges：无向边；返回无法互相到达的点对数量
        vector<int> g[n];  // 邻接表：g[u] 存放与 u 直接相连的所有节点
        for (auto& e : edges) {  // 逐条读入无向边
            int a = e[0], b = e[1];  // 取出边的两个端点
            g[a].push_back(b);  // 加入 a -> b 这条方向
            g[b].push_back(a);  // 加入 b -> a 这条反向，无向图必须双向添加
        }
        bool vis[n];  // 访问标记：DFS 时避免重复访问同一个点
        memset(vis, 0, sizeof(vis));  // 初始全部标记为未访问
        function<int(int)> dfs = [&](int i) {  // DFS：从 i 出发遍历整个连通块，返回块内节点数
            if (vis[i]) {  // 已经访问过，不再重复计数
                return 0;  // 返回 0，表示这个点不贡献新的节点
            }
            vis[i] = true;  // 标记当前点已访问
            int cnt = 1;  // 连通块大小先算上自己
            for (int j : g[i]) {  // 遍历所有邻居
                cnt += dfs(j);  // 递归累加邻居能到达的节点数
            }
            return cnt;  // 返回该连通块的节点总数
        };  // lambda 定义结束
        long long ans = 0, s = 0;  // ans：答案；s：已经处理过的所有连通块的节点总数
        for (int i = 0; i < n; ++i) {  // 枚举每个点，借此发现所有连通块
            int t = dfs(i);  // t 是 i 所在连通块的大小；已访问过的点会返回 0
            ans += s * t;  // 当前块的每个点和之前块的所有点都互不可达，新增 s*t 对
            s += t;  // 把当前块的点数并入 s
        }
        return ans;  // 返回无法互相到达的点对总数
    }
};
