// 题目：1617. 统计子树中城市之间最大距离（Count Subtrees With Max Distance Between Cities）
// 思路：枚举城市集合的位掩码，用两次 DFS 求「直径」：第一次从集合内某点出发找最远点，第二次从该点出发求最远距离，同时检查集合是否连通（msk 被清空即为连通）。
// 时间复杂度：O(2^n * n)，每个子集做两次 O(n) 的 DFS；空间复杂度：O(n + m)，邻接表与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {  // n：城市数；edges：树的边
        vector<vector<int>> g(n);  // 邻接表，下标改成 0 基后存储无向边
        for (auto& e : edges) {  // 遍历每条边
            int u = e[0] - 1, v = e[1] - 1;  // 题目编号从 1 开始，这里统一转成 0 基
            g[u].emplace_back(v);  // 记录 u → v 的边
            g[v].emplace_back(u);  // 记录 v → u 的边
        }
        vector<int> ans(n - 1);  // ans[d-1] 表示直径为 d 的子树个数，d 最大为 n-1
        int nxt = 0, msk = 0, mx = 0;  // nxt：当前最远点；msk：尚未访问的点集，同时充当访问标记；mx：当前最远距离
        function<void(int, int)> dfs = [&](int u, int d) {  // 从 u 出发在 msk 限定的点集内深搜，d 为已走距离
            msk ^= 1 << u;  // 异或相当于把 u 从「未访问」里去掉，也即标记为已访问
            if (mx < d) {  // 走到更远的点，更新最远距离
                mx = d;  // 记录新的最大距离
                nxt = u;  // 记录这个最远点，供第二次 DFS 作为起点
            }
            for (int& v : g[u]) {  // 考察 u 的所有邻居
                if (msk >> v & 1) {  // 只走仍在点集内且尚未访问的点，保证不越出子集、不重复走
                    dfs(v, d + 1);  // 继续深入，距离加一
                }
            }
        };
        for (int mask = 1; mask < 1 << n; ++mask) {  // 枚举所有非空的点子集
            if ((mask & (mask - 1)) == 0) {  // 只有一个点的子集没有距离，去掉最低位后为 0 即单点集
                continue;  // 跳过单点集
            }
            msk = mask;  // 还原待访问集合：只有 mask 里的点可以被走到
            mx = 0;  // 重置最远距离
            int cur = 31 - __builtin_clz(msk);  // 取 mask 的最高位下标作为 DFS 起点（换成哪个集合内的点都不影响直径）
            dfs(cur, 0);  // 第一次 DFS：从起点找到集合内的一个最远点 nxt
            if (msk == 0) {  // 所有点都被走到，说明这个子集是连通的，才可能是一棵子树
                msk = mask;  // 重新初始化访问标记
                mx = 0;  // 重置最远距离
                dfs(nxt, 0);  // 第二次 DFS：从 nxt 出发，最远距离就是该子树的直径
                ++ans[mx - 1];  // 按直径归类计数（直径至少为 1，所以要减一）
            }
        }
        return ans;  // 返回每种直径对应的子树个数
    }
};