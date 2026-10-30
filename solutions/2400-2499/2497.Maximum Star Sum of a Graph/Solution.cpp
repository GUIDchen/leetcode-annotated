// 题目：2497. 图中最大星和（Maximum Star Sum of a Graph）
// 思路：只有正权邻居值得选；把每个点的正权邻居点权收集起来降序排序，枚举中心取「自身权值 + 前 k 大邻居权值」的最大值。
// 时间复杂度：O(n + m + 邻居总数 log 邻居数)，m 为边数；空间复杂度：O(n + m)，邻接表存储正权邻居。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxStarSum(vector<int>& vals, vector<vector<int>>& edges, int k) {  // vals 是各点点权，edges 是无向边，k 是星形最多能带的邻居数
        int n = vals.size();  // n 是节点总数
        vector<vector<int>> g(n);  // 邻接表：g[i] 只存邻居中为正的点权，负权邻居永远不会带来收益
        for (auto& e : edges) {  // 遍历每条无向边
            int a = e[0], b = e[1];  // 取出边的两个端点
            if (vals[b] > 0) g[a].emplace_back(vals[b]);  // b 的权值为正时，才可能作为 a 的邻居贡献星和
            if (vals[a] > 0) g[b].emplace_back(vals[a]);  // a 的权值为正时，同理挂到 b 的邻居列表里
        }
        for (auto& e : g) sort(e.rbegin(), e.rend());  // 每个邻接表按从大到小排序，方便之后直接取前 k 大
        int ans = INT_MIN;  // 答案取最小整数，保证任何单点星形都能覆盖它
        for (int i = 0; i < n; ++i) {  // 枚举星形中心 i
            int v = vals[i];  // 星和先计入中心自身的权值
            for (int j = 0; j < min((int) g[i].size(), k); ++j) v += g[i][j];  // 再加上最大的 min(邻居数, k) 个正权邻居（负权邻居已在收集时过滤）
            ans = max(ans, v);  // 更新全局最大星和
        }
        return ans;  // 返回图中最大星和
    }
};