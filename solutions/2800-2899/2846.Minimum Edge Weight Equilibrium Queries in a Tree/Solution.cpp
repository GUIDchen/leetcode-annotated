// 题目：2846. 边权重均等查询（Minimum Edge Weight Equilibrium Queries in a Tree）
// 思路：BFS 预处理每点到根路径上各边权的出现次数，并用倍增表求 LCA；u→v 路径边数减去出现次数最多的那种边权的边数，即需要改动的边数。
// 时间复杂度：O((n + q) * (log n + 26))；空间复杂度：O(n * (log n + 26))，用于倍增表与边权计数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {  // n：结点数；edges：带权无向边；queries：询问的结点对
        int m = 32 - __builtin_clz(n);  // 倍增层数：2^m >= n，m 约为 log2(n) + 1
        vector<pair<int, int>> g[n];  // 邻接表：g[u] 存 (相邻结点 v, 0 基边权)
        int f[n][m];  // 倍增祖先表：f[i][j] 是 i 的第 2^j 级祖先
        int p[n];  // 每个结点的直接父结点
        int cnt[n][26];  // cnt[i][c]：从根到 i 的路径上，边权为 c 的边出现过多少次
        int depth[n];  // 每个结点的深度，根为 0
        memset(f, 0, sizeof(f));  // 祖先表清零：根的父亲保持 0（指向自己）
        memset(cnt, 0, sizeof(cnt));  // 边权计数清零
        memset(depth, 0, sizeof(depth));  // 深度清零
        memset(p, 0, sizeof(p));  // 父亲数组清零
        for (auto& e : edges) {  // 遍历边表，构建无向邻接表
            int u = e[0], v = e[1], w = e[2] - 1;  // u、v 是端点，w 减 1 把边权转成 0..25 的下标
            g[u].emplace_back(v, w);  // 从 u 出发的这条边
            g[v].emplace_back(u, w);  // 从 v 出发的这条边（无向边双向加入）
        }
        queue<int> q;  // BFS 队列，用于从根开始做预处理
        q.push(0);  // 以 0 号结点为根
        while (!q.empty()) {  // 逐层遍历整棵树
            int i = q.front();  // 取出队首结点
            q.pop();  // 队首出队
            f[i][0] = p[i];  // 第 2^0 = 1 级祖先就是直接父亲
            for (int j = 1; j < m; ++j) {  // 由低到高递推更高层的祖先
                f[i][j] = f[f[i][j - 1]][j - 1];  // 2^j 级祖先 = 2^(j-1) 级祖先再往上 2^(j-1) 级
            }
            for (auto& [j, w] : g[i]) {  // 遍历 i 的所有邻居（结构化绑定取出邻接点 j 与边权 w）
                if (j != p[i]) {  // 跳过父亲，避免沿原路边往回走
                    p[j] = i;  // 记录 j 的父亲是 i
                    memcpy(cnt[j], cnt[i], sizeof(cnt[i]));  // 继承父结点的路径边权计数
                    cnt[j][w]++;  // 把 i→j 这条边权为 w 的边计入 j 的路径统计
                    depth[j] = depth[i] + 1;  // 子结点深度 = 父结点深度 + 1
                    q.push(j);  // 子结点入队，等待继续向下扩展
                }
            }
        }
        vector<int> ans;  // 每个询问的答案
        for (auto& qq : queries) {  // 逐个处理询问
            int u = qq[0], v = qq[1];  // 取出询问的两个端点
            int x = u, y = v;  // 用副本 x / y 做上跳，保留原始端点 u / v 供最后统计
            if (depth[x] < depth[y]) {  // 保证 x 是较深的那个
                swap(x, y);  // 交换，使 x 深度不小于 y
            }
            for (int j = m - 1; ~j; --j) {  // 从高位到低位把较深的 x 提到与 y 同深度
                if (depth[x] - depth[y] >= (1 << j)) {  // 高度差够 2^j 层才跳，避免跳过
                    x = f[x][j];  // x 上跳 2^j 层
                }
            }
            for (int j = m - 1; ~j; --j) {  // x 与 y 同步上跳，寻找最近公共祖先
                if (f[x][j] != f[y][j]) {  // 祖先不同说明还没越过 LCA，可以继续上跳
                    x = f[x][j];  // x 上跳 2^j 层
                    y = f[y][j];  // y 上跳 2^j 层
                }
            }
            if (x != y) {  // 若此时还没重合，LCA 是二者的共同父亲
                x = p[x];  // 再上跳一层得到 LCA
            }
            int mx = 0;  // 路径上出现次数最多的那种边权的边数
            for (int j = 0; j < 26; ++j) {  // 枚举 0..25 共 26 种边权
                mx = max(mx, cnt[u][j] + cnt[v][j] - 2 * cnt[x][j]);  // 树上差分：u→v 路径上权值为 j 的边数 = cnt[u][j] + cnt[v][j] - 2 * cnt[lca][j]
            }
            ans.push_back(depth[u] + depth[v] - 2 * depth[x] - mx);  // 路径总边数减去保留最多的那种边权，剩下的就是要改的边数
        }
        return ans;  // 返回所有询问的结果
    }
};