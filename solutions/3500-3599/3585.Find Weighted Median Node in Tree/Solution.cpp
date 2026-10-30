// 3585. 树中找到带权中位节点（Find Weighted Median Node in Tree）
// 核心思路：BFS 预处理深度、根路径距离与倍增祖先表，再用 LCA 求出查询路径总权重，最后倍增寻找路径上首个累计权重达到一半的节点。
// 复杂度：时间复杂度 O((n + q) log n)，空间复杂度 O(n log n)，其中 n 为节点数、q 为查询数。
class Solution {  // 定义题解类
public:  // 公有接口，判题器从这里调用
    vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {  // 对每个查询求出带权中位节点
        int m = 32 - __builtin_clz(n);  // 倍增层数取 n 的二进制位数
        vector<vector<pair<int, int>>> g(n);  // 邻接表，存 (邻居, 边权)
        for (auto& e : edges) {  // 遍历所有边建图
            int u = e[0], v = e[1], w = e[2];  // 拆出边的两个端点和权值
            g[u].emplace_back(v, w);  // 加入正向边
            g[v].emplace_back(u, w);  // 加入反向边
        }  // 结束建图
        vector<vector<int>> f(n, vector<int>(m));  // 倍增表 f[i][j] 表示 i 的 2^j 级祖先
        vector<int> p(n), depth(n);  // p 存父节点，depth 存深度
        vector<long long> dist(n);  // dist 存根到各节点的距离和
        queue<int> q;  // BFS 队列
        q.push(0);  // 从根节点 0 开始遍历
        while (!q.empty()) {  // 层序 BFS 做预处理
            int i = q.front();  // 取出队首节点
            q.pop();  // 弹出队首
            f[i][0] = p[i];  // 2^0 级祖先就是父节点
            for (int j = 1; j < m; ++j) {  // 递推更高层的倍增祖先
                f[i][j] = f[f[i][j - 1]][j - 1];  // 2^j 级祖先等于 2^(j-1) 级祖先的 2^(j-1) 级祖先
            }  // 结束倍增递推
            for (auto [j, w] : g[i]) {  // 遍历当前节点的所有邻居
                if (j != p[i]) {  // 跳过父节点，避免走回头路
                    p[j] = i;  // 记录邻居的父节点
                    depth[j] = depth[i] + 1;  // 邻居深度加一
                    dist[j] = dist[i] + w;  // 累加根到邻居的距离
                    q.push(j);  // 邻居入队等待处理
                }  // 结束父节点判断
            }  // 结束邻居遍历
        }  // 结束 BFS 预处理
        vector<int> ans;  // 存放每个查询的答案
        for (auto& qq : queries) {  // 逐个处理查询
            int u = qq[0], v = qq[1];  // 取出查询的两个端点
            if (u == v) {  // 两端点相同时路径长度为 0
                ans.push_back(u);  // 答案就是该节点本身
                continue;  // 跳过后续计算
            }  // 结束特判
            int x = u, y = v;  // 用 x、y 同步上跳求 LCA
            if (depth[x] < depth[y]) {  // 保证 x 是更深的一端
                swap(x, y);  // 交换使 x 更深
            }  // 结束深度对齐准备
            for (int j = m - 1; ~j; --j) {  // 从高位到低位把 x 提到与 y 同深度
                if (depth[x] - depth[y] >= (1 << j)) {  // 深度差允许跳 2^j 步时上跳
                    x = f[x][j];  // x 上跳 2^j 层
                }  // 结束本次上跳判断
            }  // 结束深度对齐
            for (int j = m - 1; ~j; --j) {  // 继续从高位到低位逼近最近公共祖先
                if (f[x][j] != f[y][j]) {  // 两个祖先不同说明还没到最近公共祖先
                    x = f[x][j];  // x 上跳 2^j 层
                    y = f[y][j];  // y 上跳 2^j 层
                }  // 结束本次判断
            }  // 结束逼近
            if (x != y) {  // 此时再上一层才是最近公共祖先
                x = p[x];  // x 移到真正的最近公共祖先上
            }  // 结束最近公共祖先修正
            long long w = dist[u] + dist[v] - 2 * dist[x];  // u 到 v 的路径总权重（即两倍带权距离）
            if (2 * (dist[u] - dist[x]) >= w) {  // 中位节点落在 u 到最近公共祖先这一段
                int cur = u;  // 从 u 开始向上爬
                for (int j = m - 1; ~j; --j) {  // 倍增查找最远的、仍不到一半权重的位置
                    int k = f[cur][j];  // 候选祖先
                    if (depth[k] >= depth[x] && 2 * (dist[u] - dist[k]) < w) {  // 未越过最近公共祖先且到 u 的权重仍不足一半
                        cur = k;  // 把 cur 上移到候选祖先
                    }  // 结束判断
                }  // 结束查找
                ans.push_back(p[cur]);  // cur 的父节点就是首个达到一半权重的节点
            } else {  // 中位节点落在最近公共祖先到 v 这一段
                int cur = v;  // 从 v 开始向上爬
                for (int j = m - 1; ~j; --j) {  // 倍增查找最远的、距 u 已达到一半权重的位置
                    int k = f[cur][j];  // 候选祖先
                    if (depth[k] > depth[x] && 2 * (dist[u] + dist[k] - 2 * dist[x]) >= w) {  // 严格在最近公共祖先之上且从 u 到该点的累计权重已达一半
                        cur = k;  // 把 cur 上移到候选祖先
                    }  // 结束判断
                }  // 结束查找
                ans.push_back(cur);  // cur 即为带权中位节点
            }  // 结束分支
        }  // 结束查询遍历
        return ans;  // 返回所有查询的答案
    }  // 结束函数
};  // 结束类定义
