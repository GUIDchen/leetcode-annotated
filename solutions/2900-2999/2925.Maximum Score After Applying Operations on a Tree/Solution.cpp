// 题目：2925. 在树上执行操作以后得到的最大分数（Maximum Score After Applying Operations on a Tree）
// 思路：树形 DP。dfs 返回 (a, b)：a 是子树内不做任何操作时的总分（也就是整棵子树的值之和，必健康），b 是子树内可执行操作且「子树根部到每条叶子的路径仍保留至少一个非零值」时的最大得分。
// 时间复杂度：O(n)，每个节点只被访问一次；空间复杂度：O(n)，邻接表加递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maximumScoreAfterOperations(vector<vector<int>>& edges, vector<int>& values) {  // edges：树的 n-1 条边；values：每个节点的值
        int n = values.size();  // 节点个数
        vector<int> g[n];  // 邻接表：g[u] 保存与 u 直接相连的所有节点
        for (auto& e : edges) {  // 逐条处理无向边
            int a = e[0], b = e[1];  // 取出这条边的两个端点
            g[a].emplace_back(b);  // 建双向边：a 的邻居加入 b
            g[b].emplace_back(a);  // 建双向边：b 的邻居加入 a
        }
        using ll = long long;  // 分数可能超出 int 范围，统一用 64 位整数
        function<pair<ll, ll>(int, int)> dfs = [&](int i, int fa) -> pair<ll, ll> {  // fa 是父节点，避免走回头路
            ll a = 0, b = 0;  // a 累加孩子的 a（子树总和），b 累加孩子的 b（健康约束下的最优分）
            bool leaf = true;  // 先假定 i 是叶子，遇到孩子再翻转
            for (int j : g[i]) {  // 遍历 i 的所有邻居
                if (j != fa) {  // 只往儿子方向递归
                    auto [aa, bb] = dfs(j, i);  // 递归求出孩子 j 的两种状态
                    a += aa;  // 汇总孩子子树的全部值
                    b += bb;  // 汇总孩子在健康约束下能拿到的最大分
                    leaf = false;  // 存在儿子，说明 i 不是叶子
                }
            }
            if (leaf) {  // 叶子不能被执行操作，否则根到它的路径和会变成 0
                return {values[i], 0LL};  // 不操作时贡献自身值；操作则非法，记 0
            }
            return {values[i] + a, max(values[i] + b, a)};  // 不操作 i 时自身值保留、儿子可以全清空（a）；操作 i 时得自身值、儿子须各自健康（values[i]+b），取较大者
        };
        auto [_, b] = dfs(0, -1);  // 从根 0 出发，父节点记 -1；只关心 b（整棵子树必须健康）
        return b;  // 返回最大分数
    }
};
