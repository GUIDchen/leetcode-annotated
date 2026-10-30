// 题目：2538. 最大价值和与最小价值和的差值（Difference Between Maximum and Minimum Price Sum）
// 思路：树形 DP。dfs 返回 (a, b)：a 为以 i 为起点、计入末端权值的最大路径和；b 为同样路径但不计末端权值。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，邻接表与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxOutput(int n, vector<vector<int>>& edges, vector<int>& price) {  // n 为节点数，edges 为无向边列表，price 为每个节点的价值
        vector<vector<int>> g(n);  // 邻接表建图
        for (auto& e : edges) {  // 遍历每条边
            int a = e[0], b = e[1];  // 取出边的两个端点
            g[a].push_back(b);  // a 指向 b 建边
            g[b].push_back(a);  // b 指向 a 建反向边，构成无向图
        }  // 建图完成
        using ll = long long;  // 给 long long 起别名，路径和可能超出 int 范围
        using pll = pair<ll, ll>;  // pll 表示 dp 返回的两个最大路径和
        ll ans = 0;  // ans 记录全局最大差值，至少为 0
        function<pll(int, int)> dfs = [&](int i, int fa) {  // 递归 lambda：i 为当前节点，fa 为父节点，返回以 i 为起点的两个最大路径和
            ll a = price[i], b = 0;  // a 至少包含 i 自身的价值；b 不计末端节点价值，所以初值为 0
            for (int j : g[i]) {  // 遍历 i 的所有邻居
                if (j != fa) {  // 跳过父节点，避免沿着来路走回去
                    auto [c, d] = dfs(j, i);  // 递归求子节点方向的结果：c 含末端价值，d 不含末端价值
                    ans = max({ans, a + d, b + c});  // 用 a+d 或 b+c 拼出一条经过 i 的路径，更新全局最大值
                    a = max(a, price[i] + c);  // 更新 a：把子节点方向更长的路径接在 i 后面继续延伸
                    b = max(b, price[i] + d);  // 更新 b：同理，但不把末端节点的价值计入
                }  // if 结束
            }  // 邻居遍历结束
            return pll{a, b};  // 返回以 i 为起点的两个最大路径和
        };  // lambda 定义结束
        dfs(0, -1);  // 从 0 号节点出发，父节点记为 -1，遍历整棵树
        return ans;  // dfs 过程中已更新好 ans，直接返回
    }  // 方法结束
};  // 类定义结束
