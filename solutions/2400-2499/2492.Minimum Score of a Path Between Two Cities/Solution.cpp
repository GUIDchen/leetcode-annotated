// 题目：2492. 两个城市间路径的最小分数（Minimum Score of a Path Between Two Cities）
// 思路：从城市 1 出发 DFS 整个连通块，路径分数取经过边的最小权值，答案就是该连通块内所有边权的最小值。
// 时间复杂度：O(n + m)，每个点与每条边各访问常数次；空间复杂度：O(n + m)，邻接表、访问数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    int minScore(int n, vector<vector<int>>& roads) {  // n 是城市数（编号 1..n），roads 是无向带权边 [a, b, w]
        vector<vector<pair<int, int>>> g(n + 1);  // 邻接表，下标 1..n，每项存 (邻居, 边权)
        for (auto& e : roads) {  // 把每条无向边拆成两条有向边建图
            int a = e[0], b = e[1], w = e[2];  // 取出这条边的两个端点与权值
            g[a].push_back({b, w});  // a 到 b 连一条权重为 w 的边
            g[b].push_back({a, w});  // b 到 a 再连一条，构成无向图
        }  // 建图完成

        vector<bool> vis(n + 1, false);  // 访问标记，防止 DFS 重复进入同一个点
        int ans = INT_MAX;  // 连通块内边权的最小值，初始为最大整数

        auto dfs = [&](this auto&& dfs, int a) -> void {  // C++23 显式对象参数写法：把 lambda 自身作为 dfs 参数，从而可以递归调用
            vis[a] = true;  // 标记当前点已访问
            for (auto& [b, w] : g[a]) {  // 遍历与 a 相邻的每条边，取出邻点 b 与权重 w
                ans = min(ans, w);  // 路径分数取经过边的最小权值，这里边遍历边更新
                if (!vis[b]) {  // 只有未访问过的邻点才继续深入
                    dfs(b);  // 递归进入邻点
                }  // 邻点处理完毕
            }  // 邻接表遍历结束
        };  // lambda 定义结束

        dfs(1);  // 从城市 1 出发，覆盖它所在的整个连通块
        return ans;  // 连通块内最小边权即最小分数（1 与 n 保证连通）
    }  // 方法结束
};  // 类定义结束
