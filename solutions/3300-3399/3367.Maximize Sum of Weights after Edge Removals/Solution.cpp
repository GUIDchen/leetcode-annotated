// 题目：3367. 移除边之后的权重最大和（Maximize Sum of Weights after Edge Removals）
// 思路：树上 DP，dfs 返回「每点度数不超过 k 时的最大和」与「给父边留一个空位时的最大和」，子边按增益 w + b - a 降序取前 k-1 条。
// 时间复杂度：O(n log n)，每个节点要对子边增益排序；空间复杂度：O(n)，邻接表与递归栈开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maximizeSumOfWeights(vector<vector<int>>& edges, int k) {  // edges：带权边三元组 (u, v, w)；k：每个节点允许保留的最大边数
        int n = edges.size() + 1;  // n 个节点共有 n - 1 条边，因此节点数是边数加一
        vector<vector<pair<int, int>>> g(n);  // 邻接表：g[u] 保存 (邻居, 边权) 组成的对
        for (auto& e : edges) {  // 逐条边建立无向图
            int u = e[0], v = e[1], w = e[2];  // 从三元组中拆出两个端点与边权
            g[u].emplace_back(v, w);  // 无向图：u 侧记录通向 v 的那条边
            g[v].emplace_back(u, w);  // 无向图：v 侧记录通向 u 的那条边
        }  // 建图结束
        using ll = long long;  // 为长整型取别名，权值和可能超过 32 位
        auto dfs = [&](this auto&& dfs, int u, int fa) -> pair<ll, ll> {  // 递归 lambda（C++23 的显式 this 参数实现自递归）：u 为当前节点，fa 为父节点
            ll s = 0;  // s：所有孩子都按「可连父边」取最优时的汇总和
            vector<ll> t;  // t：收集每条孩子边带来的正增益，供后面排序挑选
            for (auto& [v, w] : g[u]) {  // 遍历当前节点的每条邻边
                if (v == fa) {  // 遇到父节点就跳过，避免顺着树往回走
                    continue;  // 跳过父边
                }  // 结束父边判断
                auto [a, b] = dfs(v, u);  // 递归拿到孩子 v 的两种最优值：a 为可连父边，b 为给父边留空位
                s += a;  // 先把孩子的 a 累加进 s，后面再用增益替换
                ll d = w + b - a;  // 增益 = 保留这条边多得的权值：边权 + 孩子腾出空位的收益 - 孩子的 a
                if (d > 0) {  // 只保留正增益，负增益不如直接把这条边删掉
                    t.push_back(d);  // 记录这条边的增益
                }  // 结束正增益判断
            }  // 孩子遍历结束
            ranges::sort(t, greater<>());  // 增益从大到小排序，优先保留收益高的边
            for (int i = 0; i < min((int) t.size(), k - 1); ++i) {  // 每点最多连 k 条边，除父边外最多再接 k-1 个孩子
                s += t[i];  // 累加前 k-1 大的增益
            }  // 结束取增益的循环
            return {s + (t.size() >= k ? t[k - 1] : 0), s};  // 返回两种值：(连满 k 条边, 只连 k-1 条边给父边留空位)
        };  // lambda 定义结束

        auto [x, y] = dfs(0, -1);  // 从 0 号节点作为树根开始，父节点记为 -1
        return max(x, y);  // 根节点没有父边，两种状态取较大值即为答案
    }  // 方法结束
};  // 类定义结束
