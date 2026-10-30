// 题目：3067. 在带权树网络中统计可连接服务器对数目（Count Pairs of Connectable Servers in a Weighted Tree Network）
// 核心思路：枚举每个服务器作为中心，对它去掉后得到的每条分支各做一次 DFS 统计「到中心距离是 signalSpeed 整数倍」的节点数，再用「已累计节点数 × 当前分支节点数」累加跨分支的配对。
// 时间复杂度：O(n²)，n 个中心各 DFS 一次；空间复杂度：O(n)，邻接表 O(n) 加递归栈 O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> countPairsOfConnectableServers(vector<vector<int>>& edges, int signalSpeed) {  // edges：带权树的边集（e = {a, b, w}）；signalSpeed：信号速度；返回每个服务器可连接的服务器对数
        int n = edges.size() + 1;  // 树有 n 个节点、n-1 条边，所以边数加一就是节点数
        vector<pair<int, int>> g[n];  // 邻接表：g[a] 存放 {相邻节点, 边权} 对；变长数组写在栈上由编译器自动管理
        for (auto& e : edges) {  // 逐条边建图，无向图两个方向都要加边
            int a = e[0], b = e[1], w = e[2];  // 拆出边的两个端点 a、b 与权值 w
            g[a].emplace_back(b, w);  // a 的邻接表加入 (b, w)
            g[b].emplace_back(a, w);  // b 的邻接表加入 (a, w)，完成无向边的反向登记
        }
        function<int(int, int, int)> dfs = [&](int a, int fa, int ws) {  // 递归函数：从 a 出发、父节点为 fa、到 a 的路径权和是 ws，返回该分支里满足 ws' % signalSpeed == 0 的节点数
            int cnt = ws % signalSpeed == 0;  // 先判断起点 a 自身：权和能被 signalSpeed 整除时计数为 1，否则为 0
            for (auto& [b, w] : g[a]) {  // 遍历 a 的所有邻居，结构化绑定出邻居 b 与边权 w
                if (b != fa) {  // 跳过父节点，避免沿着来路往回走、造成重复搜索
                    cnt += dfs(b, a, ws + w);  // 继续深入子树，路径权和累加边权 w，把答案加进 cnt
                }
            }
            return cnt;  // 返回本分支内符合条件的节点总数
        };  // 递归函数定义结束
        vector<int> ans(n);  // 答案数组：ans[a] 表示以 a 为中心的服务器对数，初始化全 0
        for (int a = 0; a < n; ++a) {  // 枚举树上的每一个节点 a，把它当作中心服务器
            int s = 0;  // s：已经扫过的分支中符合条件的节点总数（跨分支配对的累积量）
            for (auto& [b, w] : g[a]) {  // 枚举 a 的每一条分支；去掉 a 之后这些分支彼此不连通，只有跨分支的节点对才合法
                int t = dfs(b, a, w);  // 当前分支内符合条件的节点数 t
                ans[a] += s * t;  // 当前分支的每个节点都能与之前各分支的 s 个节点配对，故累加 s * t
                s += t;  // 把当前分支的节点数并入 s，供后面的分支使用
            }
        }
        return ans;  // 返回所有服务器作为中心时的可连接对数
    }
};
