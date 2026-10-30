// 题目：2378. 选择边来最大化树的得分（Choose Edges to Maximize Score in a Tree）
// 思路：树上最大权匹配的树形 DP。dfs(i) 返回 (父边被选中时子树最优值, 父边未被选中时子树最优值)；父边被选则子边全禁，父边未选则可用「w + 选子边的子树值 - 不选子边的子树值」挑一条净增益最大的子边。
// 时间复杂度：O(n)，每个节点只被 DFS 访问一次；空间复杂度：O(n)，邻接表与递归栈各占 O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxScore(vector<vector<int>>& edges) {  // edges[i] = [父节点, 边权]，返回能选出的一组互不相邻的边的最大权值和
        int n = edges.size();  // 节点数等于边信息条数（edges[0] 是根的占位项）
        vector<vector<pair<int, int>>> g(n);  // 邻接表：g[p] 保存 p 的所有 (子节点, 边权) 对
        for (int i = 1; i < n; ++i) {  // 从下标 1 开始建图，跳过根的占位项 edges[0] = [-1, -1]
            int p = edges[i][0], w = edges[i][1];  // 拆出节点 i 的父节点 p 与这条边的权重 w
            g[p].emplace_back(i, w);  // 把子节点 i 连同边权挂到父节点 p 的邻接表上
        }  // 建图结束
        using ll = long long;  // 起类型别名，减少 long long 的重复书写
        using pll = pair<ll, ll>;  // 二元组类型：dfs 返回 (父边被选, 父边未被选) 两种状态下的最优得分
        function<pll(int)> dfs = [&](int i) -> pll {  // 递归函数：i 为当前子树根；捕获外部变量以访问邻接表 g
            ll a = 0, b = 0, t = 0;  // a：父边被选中时该子树得分；b：父边未被选中时该子树得分；t：额外选一条子边的最大净增益
            for (auto& [j, w] : g[i]) {  // 遍历 i 的每条子边 (i, j)，其权重为 w
                auto [x, y] = dfs(j);  // 递归求出子节点 j 的两种状态值：x = 选中断开/选中这条子边后的值，y = 不选这条边的值
                a += y;  // 父边被选时 i 已被占用，子边一条都不能选，故只累加子树的「父边未选」值 y
                b += y;  // 父边未被选时先按「子边全不选」累加 y，稍后再决定是否加一条子边的增益
                t = max(t, x - y + w);  // 选中 (i, j) 的净增益为 w + x - y，在所有子边中取最大
            }  // 子边枚举结束
            b += t;  // 至多再选一条子边：加入最优增益 t（t 保持 0 表示一条都不选）
            return make_pair(a, b);  // 按 (父边被选, 父边未被选) 的顺序返回两个值
        };  // 递归 lambda 定义结束
        return dfs(0).second;  // 根节点没有父边，等价于「父边未被选中」，故取 second
    }  // maxScore 方法结束
};  // Solution 类结束
