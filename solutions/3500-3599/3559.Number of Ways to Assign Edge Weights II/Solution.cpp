// 3559. 给边赋权值的方案数 II / Number of Ways to Assign Edge Weights II
// 核心思路：BFS 建树同时用倍增法预处理祖先表与深度，每个询问先对齐深度再用倍增求最近公共祖先，距离 d 对应的方案数为 2^(d-1)。
// 复杂度：预处理 O(n log n)，每次询问 O(log n)，空间 O(n log n)
class Solution {  // 定义解题类
public:  // 公有接口
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {  // 返回每个询问的赋权方案数
        int n = edges.size() + 1;  // 结点数等于边数加一
        int m = 32 - __builtin_clz(n);  // 倍增层数，即 log2(n) 向上取整
        vector<vector<int>> g(n + 1);  // 邻接表，下标从 1 开始
        for (auto& e : edges) {  // 遍历每条边建立无向图
            int u = e[0], v = e[1];  // 取出边的两个端点
            g[u].push_back(v);  // u 的邻居加入 v
            g[v].push_back(u);  // v 的邻居加入 u
        }  // 结束建图
        vector<vector<int>> f(n + 1, vector<int>(m));  // 倍增祖先表 f[结点][层]
        vector<int> p(n + 1), depth(n + 1);  // 父结点数组与深度数组
        queue<int> q;  // BFS 队列
        q.push(1);  // 根结点 1 入队
        while (!q.empty()) {  // 队列非空时逐层处理
            int i = q.front();  // 取出队首结点 i
            q.pop();  // 弹出队首
            f[i][0] = p[i];  // 第 0 层祖先就是父结点
            for (int j = 1; j < m; ++j) {  // 递推更高层的祖先
                f[i][j] = f[f[i][j - 1]][j - 1];  // 2^j 祖先等于 2^(j-1) 祖先的 2^(j-1) 祖先
            }  // 结束祖先递推
            for (int j : g[i]) {  // 枚举结点 i 的邻居
                if (j != p[i]) {  // 跳过父结点，只处理子结点
                    p[j] = i;  // 记录子结点的父结点
                    depth[j] = depth[i] + 1;  // 子结点深度加一
                    q.push(j);  // 子结点入队
                }  // 结束子结点判断
            }  // 结束邻居枚举
        }  // 结束 BFS
        const int mod = 1e9 + 7;  // 取模常量
        vector<int> pow2(n, 1);  // 预处理 2 的幂表
        for (int i = 1; i < n; ++i) {  // 递推填充幂表
            pow2[i] = pow2[i - 1] * 2 % mod;  // 前一项乘二再取模
        }  // 结束幂表构造
        vector<int> ans;  // 保存每个询问的答案
        for (auto& qq : queries) {  // 逐个处理询问
            int u = qq[0], v = qq[1];  // 取出询问的两个结点
            int x = u, y = v;  // 用副本向上跳，保留原来的深度值
            if (depth[x] < depth[y]) {  // 保证 x 是较深的那个结点
                swap(x, y);  // 交换使 x 更深
            }  // 结束深度对齐前的交换
            for (int j = m - 1; ~j; --j) {  // 从高层到低层把 x 提到与 y 同深度
                if (depth[x] - depth[y] >= (1 << j)) {  // 跳 2^j 步仍不会越过 y
                    x = f[x][j];  // x 向上跳 2^j 层
                }  // 结束这一步判断
            }  // 结束深度对齐
            for (int j = m - 1; ~j; --j) {  // 再从高层到低层同时上跳找分歧祖先
                if (f[x][j] != f[y][j]) {  // 两个祖先不同说明还没到 LCA
                    x = f[x][j];  // x 上跳到该层祖先
                    y = f[y][j];  // y 上跳到该层祖先
                }  // 结束这一步判断
            }  // 结束找 LCA 的上跳
            if (x != y) {  // 仍未相遇则 LCA 是当前 x 的父结点
                x = p[x];  // 走到真正的 LCA
            }  // 结束 LCA 修正
            int d = depth[u] + depth[v] - 2 * depth[x];  // 两点间边数等于深度和的二倍 LCA 深度修正
            ans.push_back(d == 0 ? 0 : pow2[d - 1]);  // 距离为 d 时方案数为 2^(d-1)，同一结点则为 0
        }  // 结束询问处理
        return ans;  // 返回答案数组
    }  // 结束 assignEdgeWeights
};  // 结束类定义
