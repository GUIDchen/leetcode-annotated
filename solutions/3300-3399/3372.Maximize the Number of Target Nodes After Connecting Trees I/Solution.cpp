// 题目：3372. 连接两棵树后最大目标节点数目 I（Maximize the Number of Target Nodes After Connecting Trees I）
// 思路：目标节点是与连接点在 k 步以内的节点。第二棵树任选一点作连接点，只消耗 1 条边，对每个点做 DFS 取最大贡献 t；再对第一棵树每个点统计距离 ≤ k 的节点数并与 t 相加。
// 时间复杂度：O(n·m)，n、m 为两棵树节点数，每个节点都做一次 DFS；空间复杂度：O(n+m)，邻接表与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2, int k) {  // edges1/edges2 是两棵树的边；k 是允许的最远距离
        auto g2 = build(edges2);  // 先建第二棵树的邻接表
        int m = edges2.size() + 1;  // 第二棵树的节点数 = 边数 + 1
        int t = 0;  // t 保存第二棵树能贡献的最大目标节点数
        for (int i = 0; i < m; ++i) {  // 枚举第二棵树中每个节点作为连接点
            t = max(t, dfs(g2, i, -1, k - 1));  // 连接本身要消耗 1 条边，所以第二棵树内只剩 k-1 的距离预算
        }  // 枚举完所有连接点，t 即第二棵树的最大贡献

        auto g1 = build(edges1);  // 建第一棵树的邻接表
        int n = edges1.size() + 1;  // 第一棵树的节点数 = 边数 + 1

        vector<int> ans(n, t);  // 每个答案先统一加上第二棵树的贡献 t
        for (int i = 0; i < n; ++i) {  // 枚举第一棵树的每个节点作为连接点
            ans[i] += dfs(g1, i, -1, k);  // 再加上第一棵树内与 i 距离不超过 k 的节点数
        }  // 答案数组填完

        return ans;  // 返回每个节点的最大目标节点数
    }  // 方法结束

private:  // 以下为私有辅助函数
    vector<vector<int>> build(const vector<vector<int>>& edges) {  // 把边列表转换成邻接表
        int n = edges.size() + 1;  // 节点数 = 边数 + 1
        vector<vector<int>> g(n);  // 初始化 n 个空的邻接表
        for (const auto& e : edges) {  // 遍历每条边
            int a = e[0], b = e[1];  // 取出边的两个端点
            g[a].push_back(b);  // a -> b 这条有向边
            g[b].push_back(a);  // b -> a，无向边需要双向存储
        }  // 边处理完毕
        return g;  // 返回建好的图
    }  // build 函数结束

    int dfs(const vector<vector<int>>& g, int a, int fa, int d) {  // dfs：统计与节点 a 距离不超过 d 的节点数，fa 是父节点用于防止走回头路
        if (d < 0) {  // 距离预算已经用尽
            return 0;  // 再走一步就超距离，返回 0
        }  // 判断结束
        int cnt = 1;  // 自己算 1 个目标节点
        for (int b : g[a]) {  // 遍历 a 的所有邻居
            if (b != fa) {  // 跳过父节点，避免在树上原地打转
                cnt += dfs(g, b, a, d - 1);  // 预算减 1，递归统计子节点能覆盖的节点数
            }  // 邻居遍历完
        }  // 子树统计结束
        return cnt;  // 返回以 a 为根、距离不超过 d 的节点总数
    }  // dfs 函数结束
};  // 题解类定义结束
