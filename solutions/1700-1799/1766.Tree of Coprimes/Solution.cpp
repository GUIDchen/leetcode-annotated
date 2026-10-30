// 题目：1766. 互质树（Tree of Coprimes）
// 思路：先预处理 1..50 中两两互质的数对；再 DFS 遍历树，为每个值维护一条「祖先栈」（元素为节点下标 + 深度），进入节点时压栈、回溯时出栈；对当前节点枚举与 nums[i] 互质的值，取对应栈顶中最深（离自己最近）的祖先作为答案。
// 时间复杂度：O(50^2 + n * 50)，每个节点最多枚举 50 个互质候选值；空间复杂度：O(n + 50^2)，邻接表、答案数组与 51 条栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) {  // nums：每个节点的值（1..50）；edges：无向边；返回每个节点最近的互质祖先
        int n = nums.size();  // 节点个数
        vector<vector<int>> g(n);  // 邻接表，用来建树
        vector<vector<int>> f(51);  // f[v] 保存 1..50 中所有与 v 互质的值（避免 DFS 时反复算 gcd）
        vector<stack<pair<int, int>>> stks(51);  // stks[v] 是值为 v 的节点在当前 DFS 路径上的栈，元素为 (节点下标, 深度)
        for (auto& e : edges) {  // 遍历每条无向边
            int u = e[0], v = e[1];  // 取出这条边的两个端点
            g[u].emplace_back(v);  // u 到 v 连边
            g[v].emplace_back(u);  // v 到 u 连边（无向图要双向建边）
        }  // 建图结束
        for (int i = 1; i < 51; ++i) {  // 预处理互质表：枚举第一个值 i
            for (int j = 1; j < 51; ++j) {  // 枚举第二个值 j
                if (__gcd(i, j) == 1) {  // 最大公约数为 1 就说明 i 与 j 互质
                    f[i].emplace_back(j);  // 把 j 记入 f[i] 的候选列表
                }
            }
        }
        vector<int> ans(n);  // 答案数组：ans[i] 表示节点 i 最近的互质祖先
        function<void(int, int, int)> dfs = [&](int i, int fa, int depth) {  // 递归 DFS 的 lambda：i 当前节点，fa 父节点，depth 当前深度
            int t = -1, k = -1;  // t 记录答案节点，k 记录该祖先的深度；-1 表示还没找到
            for (int v : f[nums[i]]) {  // 枚举所有与 nums[i] 互质的值
                auto& stk = stks[v];  // 取出该值对应的祖先栈（引用，避免拷贝）
                if (!stk.empty() && stk.top().second > k) {  // 栈非空且栈顶深度更大，说明它比当前答案更近
                    t = stk.top().first;  // 更新答案为该祖先节点
                    k = stk.top().second;  // 记录它的深度，供后面的候选值比较
                }
            }
            ans[i] = t;  // 写入当前节点的答案（找不到互质祖先时仍为 -1）
            for (int j : g[i]) {  // 遍历当前节点的所有邻居
                if (j != fa) {  // 跳过父节点，避免沿着来路走回去
                    stks[nums[i]].push({i, depth});  // 把当前节点按 (下标, 深度) 压入「值 → 栈」，供子树查询祖先
                    dfs(j, i, depth + 1);  // 递归处理子节点，深度加 1
                    stks[nums[i]].pop();  // 回溯：弹出当前节点，保证栈里只剩真正的祖先
                }
            }
        };  // lambda 定义结束
        dfs(0, -1, 0);  // 从根节点 0 开始 DFS；根没有父节点所以传 -1，深度为 0
        return ans;  // 返回答案数组
    }  // 方法结束
};  // 类定义结束
