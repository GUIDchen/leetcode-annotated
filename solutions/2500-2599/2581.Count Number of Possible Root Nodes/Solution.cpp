// 题目：2581. 统计可能的树根数目（Count Number of Possible Root Nodes）
// 思路：先把树定根在 0，一遍 DFS 算出成立的猜测数 cnt；再换根 DP，根从 i 移到子节点 j 时只增量调整 (i,j) 与 (j,i) 两条边的贡献，避免每次重新统计。
// 时间复杂度：O(n + m)，两次 DFS 各线性，m 为 guesses 长度；空间复杂度：O(n + m)，邻接表、猜测哈希表与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {  // edges 为无向树的边，guesses 为猜测的父子关系，k 为要求成立的最少猜测数
        int n = edges.size() + 1;  // n 个节点的树恰好有 n-1 条边，所以节点数等于边数加一
        vector<int> g[n];  // 邻接表：g[u] 保存 u 的所有邻居
        unordered_map<long long, int> gs;  // gs 记录每条有向边 (父, 子) 被猜测了多少次
        auto f = [&](int i, int j) {  // 把有序点对 (i, j) 编码成一个 long long 键，省去自定义 pair 哈希
            return 1LL * i * n + j;  // i 乘上 n 再加 j，不同点对不会撞键
        };
        for (auto& e : edges) {  // 根据边表建无向图
            int a = e[0], b = e[1];  // 取出这条边的两个端点
            g[a].push_back(b);  // a 的邻居里加入 b
            g[b].push_back(a);  // b 的邻居里加入 a，无向图两个方向都要存
        }
        for (auto& e : guesses) {  // 统计每条猜测出现的次数
            int a = e[0], b = e[1];  // 猜测的父节点 a 与子节点 b
            gs[f(a, b)]++;  // 键 (a, b) 的计数加一
        }
        int ans = 0;  // ans 记录满足条件的根的数量
        int cnt = 0;  // cnt 记录以当前节点为根时成立的猜测数，换根时增量维护

        function<void(int, int)> dfs1 = [&](int i, int fa) {  // 第一遍 DFS：以 0 为根，把成立的猜测数累加到 cnt
            for (int& j : g[i]) {  // 遍历 i 的所有邻居
                if (j != fa) {  // 跳过父节点，保证只往子树方向走，不会绕回
                    cnt += gs[f(i, j)];  // 若 (i, j) 这条父子关系被猜过，对应猜测在此根下成立
                    dfs1(j, i);  // 以 i 为父继续递归 j 的子树
                }
            }
        };

        function<void(int, int)> dfs2 = [&](int i, int fa) {  // 第二遍 DFS：换根，把根从 i 移动到子节点 j 时只增量更新 cnt
            ans += cnt >= k;  // cnt >= k 说明当前根合法；bool 隐式转换成 0/1 累加到答案
            for (int& j : g[i]) {  // 枚举可以换根的方向
                if (j != fa) {  // 只对子节点换根，父方向在上一层已处理过
                    int a = gs[f(i, j)];  // 换根后 (i, j) 不再是父子关系，这部分猜测会失效
                    int b = gs[f(j, i)];  // 换根后 (j, i) 成为父子关系，这部分猜测开始成立
                    cnt -= a;  // 先减掉旧方向的贡献
                    cnt += b;  // 再加上新方向的贡献
                    dfs2(j, i);  // 以 j 为根继续统计它的子树
                    cnt -= b;  // 回溯：撤掉 (j, i) 的贡献
                    cnt += a;  // 回溯：恢复 (i, j) 的贡献，保证兄弟分支用的是同一份 cnt
                }
            }
        };
        dfs1(0, -1);  // 以节点 0 为根做第一次统计，-1 表示没有父节点
        dfs2(0, -1);  // 换根枚举所有可能的根
        return ans;  // 返回合法根的个数
    }
};
