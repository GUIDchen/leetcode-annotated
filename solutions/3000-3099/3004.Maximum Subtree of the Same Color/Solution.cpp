// 题目：3004. 相同颜色的最大子树（Maximum Subtree of the Same Color）
// 核心思路：无向树邻接表 + 后序 DFS：dfs 返回「以当前节点为根的子树是否整体同色」，同时累计子树大小，同色时用大小更新答案。
// 时间复杂度：O(n)，每个节点只被访问一次；空间复杂度：O(n)，邻接表、size 数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumSubtreeSize(vector<vector<int>>& edges, vector<int>& colors) {  // edges：树的 n-1 条无向边；colors：每个节点的颜色（0 或 1）
        int n = edges.size() + 1;  // 边数 + 1 就是节点数
        vector<int> g[n];  // 邻接表：g[u] 保存与 u 直接相连的所有节点
        vector<int> size(n, 1);  // size[u] 表示以 u 为根的子树的节点个数，单个节点初始为 1
        for (auto& e : edges) {  // 遍历每条边，把无向树建成邻接表
            int a = e[0], b = e[1];  // 取出这条边的两个端点
            g[a].push_back(b);  // a 的邻居列表里加入 b
            g[b].push_back(a);  // b 的邻居列表里加入 a，无向图两个方向都要加
        }  // 建图完成
        int ans = 0;  // ans 记录「同色子树」的最大节点数
        function<bool(int, int)> dfs = [&](int a, int fa) {  // 后序 DFS：返回以 a 为根、父节点为 fa 的子树是否整体同色
            bool ok = true;  // 先假设当前子树同色，之后一旦不满足就置为 false
            for (int b : g[a]) {  // 枚举 a 的每个邻居
                if (b != fa) {  // 跳过父节点，避免沿原路回走造成死循环
                    bool t = dfs(b, a);  // 先递归处理子节点 b，得到 b 那棵子树是否同色
                    ok = ok && colors[a] == colors[b] && t;  // a 与 b 同色、且 b 的子树同色时，a 的子树才可能仍然同色
                    size[a] += size[b];  // 子树大小 = 自身 + 各子节点子树大小，这里逐个累加
                }  // if (b != fa) 分支结束
            }  // 所有邻居处理完毕
            if (ok) {  // 走到这里 ok 仍为 true，说明以 a 为根的整棵子树颜色都相同
                ans = max(ans, size[a]);  // 用这棵同色子树的节点数更新答案
            }  // if (ok) 分支结束
            return ok;  // 把同色与否回传给父节点
        };  // lambda 定义结束
        dfs(0, -1);  // 以 0 号节点为整棵树的根开始 DFS，-1 表示没有父节点
        return ans;  // 返回最大同色子树的节点数
    }
};
