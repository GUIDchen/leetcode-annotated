// 题目：2973. 树中每个节点放置的金币数目（Find Number of Coins to Place in Tree Nodes）
// 思路：建树后自底向上 DFS，把每棵子树的花费排序；节点金币数取「最大三数之积」与「最小两负数乘最大数」的较大者；向上只回传最小两个和最大三个以剪枝。
// 时间复杂度：O(n log n)（排序，回传列表长度不超过 5）；空间复杂度：O(n)（邻接表与递归栈）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<long long> placedCoins(vector<vector<int>>& edges, vector<int>& cost) {  // edges：树的 n-1 条无向边；cost：每个节点的花费；返回每个节点放置的金币数目
        int n = cost.size();  // n 即节点个数（节点编号 0..n-1）
        vector<long long> ans(n, 1);  // 答案数组，默认 1：题面规定不足 3 个节点时只能放 1 枚金币
        vector<int> g[n];  // 邻接表：g[v] 保存 v 的所有邻居（变长数组即可）
        for (auto& e : edges) {  // 遍历每条边建立双向连接
            int a = e[0], b = e[1];  // 取出边的两个端点
            g[a].push_back(b);  // a 的邻居加入 b
            g[b].push_back(a);  // b 的邻居加入 a，构成无向图
        }  // 建图结束
        function<vector<int>(int, int)> dfs = [&](int a, int fa) -> vector<int> {  // 自底向上 DFS：返回以 a 为根的子树中「排序后的花费列表」，fa 是父节点
            vector<int> res = {cost[a]};  // 先把自己的花费放进列表
            for (int b : g[a]) {  // 枚举所有邻居
                if (b != fa) {  // 跳过父节点，防止走回头路（树根用 -1 表示没有父节点）
                    auto t = dfs(b, a);  // 递归求出子树的花费列表
                    res.insert(res.end(), t.begin(), t.end());  // 把子树列表整体拼接到当前列表末尾，稍后统一排序
                }  // 分支结束
            }  // 邻居遍历结束
            sort(res.begin(), res.end());  // 排序后：最小值在最前两个，最大值在最后三个，便于取极值
            int m = res.size();  // m 为当前子树的节点个数
            if (m >= 3) {  // 至少 3 个节点才能放 3 枚金币
                long long x = 1LL * res[m - 1] * res[m - 2] * res[m - 3];  // 方案一：取最大的三个数相乘（全为正数时最优），1LL 保证 64 位乘法
                long long y = 1LL * res[0] * res[1] * res[m - 1];  // 方案二：取最小两个负数与最大正数相乘（负负得正，可能更大）
                ans[a] = max({0LL, x, y});  // 与 0 取较大值：三数之积为负时按题面放 0 枚金币
            }  // 分支结束
            if (m >= 5) {  // 只需极值即可覆盖所有最优组合，故节点数超过 5 时裁剪
                res = {res[0], res[1], res[m - 1], res[m - 2], res[m - 3]};  // 向上传最小两个与最大三个，把空间和排序代价压到常数级
            }  // 分支结束
            return res;  // 返回给父节点合并
        };  // lambda 定义结束
        dfs(0, -1);  // 从根节点 0 开始 DFS，-1 表示没有父节点
        return ans;  // 返回每个节点的金币数目
    }  // 方法结束
};  // 类结束
