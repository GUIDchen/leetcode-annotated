// 题目：2039. 网络空闲的时刻（The Time When the Network Becomes Idle）
// 思路：以主服务器 0 为源做 BFS 求每个数据服务器的单程距离 d，其往返时间 t = 2d；最后一个重发时刻为 (t-1)/patience*patience，空闲时刻即该时刻加 t 再加 1。
// 时间复杂度：O(n + m)，BFS 中每条边只被访问常数次；空间复杂度：O(n + m)，邻接表与队列的规模。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& patience) {  // edges：无向边集合；patience：每个数据服务器的重发间隔
        int n = patience.size();  // n：数据服务器数量（编号 0..n-1，0 是主服务器）
        vector<int> g[n];  // 变长数组充当邻接表，g[u] 保存 u 的全部邻居
        for (auto& e : edges) {  // 逐条边构建无向图
            int u = e[0], v = e[1];  // 取出这条边的两个端点
            g[u].push_back(v);  // u 的邻居中加入 v
            g[v].push_back(u);  // v 的邻居中加入 u，无向边两个方向都要加
        }
        queue<int> q{{0}};  // BFS 队列，起点是主服务器 0
        bool vis[n];  // vis：节点是否已入队，防止重复访问
        memset(vis, false, sizeof(vis));  // 全部初始化为 false（未访问）
        vis[0] = true;  // 主服务器自身标记为已访问
        int ans = 0, d = 0;  // ans：最终的空闲时刻；d：当前层数，即到主服务器的单程距离
        while (!q.empty()) {  // 队列非空就继续逐层扩展
            ++d;  // 进入下一层，单程距离加一
            int t = d * 2;  // 往返时间 t = 2d，即发出请求到收到回复的时间
            for (int i = q.size(); i; --i) {  // 固定当前层的节点数，本轮只处理这一层的节点
                int u = q.front();  // 取出队首节点
                q.pop();  // 出队
                for (int v : g[u]) {  // 遍历 u 的所有邻居
                    if (!vis[v]) {  // 只关心尚未访问的邻居（BFS 保证首次到达即最短距离）
                        vis[v] = true;  // 标记已访问，保证每个节点只入队一次
                        q.push(v);  // 邻居入队，留到下一层计算距离
                        ans = max(ans, (t - 1) / patience[v] * patience[v] + t + 1);  // 最后一次重发时刻是 (t-1)/patience[v]*patience[v]（严格早于 t），加往返 t 与空闲判定的 1 秒；对所有节点取最大值
                    }
                }
            }
        }
        return ans;  // 返回全网络最晚变为空闲的时刻
    }
};