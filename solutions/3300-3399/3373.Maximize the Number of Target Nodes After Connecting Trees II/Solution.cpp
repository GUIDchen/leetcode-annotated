// 题目：3373. 连接两棵树后最大目标节点数目 II（Maximize the Number of Target Nodes After Connecting Trees II）
// 思路：本题没有距离上限 k，「目标节点」要求与连接点距离为偶数。对两棵树做二分图染色（距离奇偶），树 2 可任选连接点，取两种颜色计数的较大者 t；树 1 中每个点只能拿到与它同色的节点数，加上 t 即为答案。
// 时间复杂度：O(n+m)，每棵树只做一次 DFS 染色；空间复杂度：O(n+m)，邻接表、颜色数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {  // edges1/edges2 分别是两棵树的边，本题不需要距离上限 k
        auto g1 = build(edges1);  // 建第一棵树的邻接表
        auto g2 = build(edges2);  // 建第二棵树的邻接表
        int n = g1.size(), m = g2.size();  // n、m 分别是两棵树的节点数
        vector<int> c1(n, 0), c2(m, 0);  // c1[i]/c2[i] 记录节点 i 的染色值，即到根的奇偶性
        vector<int> cnt1(2, 0), cnt2(2, 0);  // cnt1/cnt2 按颜色统计每棵树中两种颜色的节点个数

        dfs(g2, 0, -1, c2, 0, cnt2);  // 对第二棵树从节点 0 开始染色并统计两种颜色
        dfs(g1, 0, -1, c1, 0, cnt1);  // 对第一棵树同样染色并统计

        int t = max(cnt2[0], cnt2[1]);  // 第二棵树上总能选到某种颜色的全部节点，取较大者作为贡献 t
        vector<int> ans(n);  // 答案数组：存放每个节点作为连接点时的目标节点数
        for (int i = 0; i < n; ++i) {  // 枚举第一棵树的每个节点作为连接点
            ans[i] = t + cnt1[c1[i]];  // 与 i 同色的第一棵树节点数 + 第二棵树的贡献 t
        }  // 答案填完
        return ans;  // 返回每个节点的最大目标节点数
    }  // 方法结束

private:  // 以下为私有辅助函数
    vector<vector<int>> build(const vector<vector<int>>& edges) {  // 把边列表转换成邻接表
        int n = edges.size() + 1;  // 节点数 = 边数 + 1
        vector<vector<int>> g(n);  // 初始化 n 个空的邻接表
        for (const auto& e : edges) {  // 遍历每条边
            int a = e[0], b = e[1];  // 取出边的两个端点
            g[a].push_back(b);  // a -> b 这条有向边
            g[b].push_back(a);  // b -> a，无向边要双向存储
        }  // 边处理完毕
        return g;  // 返回建好的图
    }  // build 函数结束

    void dfs(const vector<vector<int>>& g, int a, int fa, vector<int>& c, int d, vector<int>& cnt) {  // dfs：给连通块染色，a 是当前节点，fa 是父节点，c 存颜色，d 是当前颜色，cnt 统计各颜色节点数
        c[a] = d;  // 记录节点 a 的颜色
        cnt[d]++;  // 对应颜色的节点数加一
        for (int b : g[a]) {  // 遍历 a 的所有邻居
            if (b != fa) {  // 跳过父节点，避免在树上原地打转
                dfs(g, b, a, c, d ^ 1, cnt);  // 子节点的颜色取反（d ^ 1 即 0/1 互换），继续递归
            }  // 邻居遍历完
        }  // 当前节点处理结束
    }  // dfs 函数结束
};  // 题解类定义结束
