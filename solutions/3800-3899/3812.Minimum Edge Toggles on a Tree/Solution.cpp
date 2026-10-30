// 3812. Minimum Edge Toggles on a Tree | 翻转树上最少边
// 核心思路：树上 DFS，自底向上判断每棵子树根的 start/target 字符是否仍不一致；子节点不一致就翻转它与父亲之间的那条边（同时把父亲的标记取反），根节点仍不一致则无解。
// 复杂度：时间 O(n log n)（一次 DFS + 对答案排序）；空间 O(n)（邻接表与递归栈）。
class Solution {  // 定义题解类
public:  // 公有接口
    vector<int> minimumFlips(int n, vector<vector<int>>& edges, string start, string target) {  // 返回需要翻转的边下标（升序）；无法使 start 变成 target 时返回 {-1}
        vector<pair<int, int>> g[n];  // 邻接表：每个点存若干 (邻居, 边下标)
        for (int i = 0; i < n - 1; ++i) {  // 按输入顺序建边，边下标就是题目要求的编号
            int a = edges[i][0], b = edges[i][1];  // 取出第 i 条边的两个端点
            g[a].push_back({b, i});  // a 一侧记录通向 b 的第 i 号边
            g[b].push_back({a, i});  // b 一侧记录通向 a 的第 i 号边
        }  // 建图完成
        vector<int> ans;  // 收集需要翻转的边下标
        auto dfs = [&](this auto&& dfs, int a, int fa) -> bool {  // 自递归 lambda：返回以 a 为根的子树是否还需要向上翻转（即 a 的字符是否仍与目标不一致）
            bool rev = start[a] != target[a];  // 先只看节点 a 自身的 start 与 target 是否不同
            for (auto [b, i] : g[a]) {  // 遍历 a 的所有邻边
                if (b != fa && dfs(b, a)) {  // 跳过父边；子树返回真说明必须翻转 a-b 这条边
                    ans.push_back(i);  // 记录被翻转的边下标
                    rev = !rev;  // 翻边会连带把 a 自身也翻转，所以自己的标记取反
                }  // 结束子节点处理
            }  // 邻边遍历结束
            return rev;  // 把 a 的最终标记交回给父节点
        };  // dfs lambda 定义结束
        if (dfs(0, -1)) {  // 根节点若仍有残留标记，说明差异无法被任何翻边消除
            return {-1};  // 按题意返回 {-1}
        }  // 结束无解分支
        ranges::sort(ans);  // 按题目要求把边下标升序排列
        return ans;  // 返回结果
    }  // 方法结束
};  // 类定义结束
