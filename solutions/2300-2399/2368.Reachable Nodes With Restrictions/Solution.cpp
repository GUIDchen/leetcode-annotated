// 题目：2368. 受限条件下可到达节点的数目（Reachable Nodes With Restrictions）
// 核心思路：先由 edges 建无向邻接表，把 restricted 里的节点预标记为已访问当成墙，再从 0 号节点做一次 DFS 统计可达节点数。
// 时间复杂度：O(n)，每条边与每个节点都只被访问常数次；空间复杂度：O(n)，邻接表、访问标记与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int reachableNodes(int n, vector<vector<int>>& edges, vector<int>& restricted) {  // n：节点个数；edges：无向边；restricted：不允许经过的节点
        vector<int> g[n];  // 邻接表：g[i] 存放与节点 i 直接相连的所有节点
        vector<int> vis(n);  // 访问标记数组，初值 0 表示尚未访问
        for (auto& e : edges) {  // 逐条读入无向边
            int a = e[0], b = e[1];  // 取出这条边的两个端点
            g[a].emplace_back(b);  // 建立 a → b 的边
            g[b].emplace_back(a);  // 建立 b → a 的边，两条合起来才是无向图
        }  // 建图循环结束
        for (int i : restricted) {  // 把受限节点提前标记为已访问，DFS 自然就不会进入它们
            vis[i] = true;  // 相当于把这些节点当作一堵墙
        }  // 受限节点标记结束
        function<int(int)> dfs = [&](int i) {  // 递归 lambda：返回从节点 i 出发能到达的节点个数
            vis[i] = true;  // 一进入就标记，既避免重复计数也避免死循环
            int ans = 1;  // 节点 i 本身算一个
            for (int j : g[i]) {  // 遍历 i 的所有邻居
                if (!vis[j]) {  // 只有未访问过（且不是受限节点）的邻居才继续深入
                    ans += dfs(j);  // 累加该邻居能到达的节点数量
                }  // if 分支结束
            }  // 邻居遍历结束
            return ans;  // 返回以 i 为根能到达的节点总数
        };  // lambda 定义结束（结尾分号不能少）
        return dfs(0);  // 从 0 号节点出发统计，即题目要求的答案
    }  // 方法结束
};  // 类定义结束
