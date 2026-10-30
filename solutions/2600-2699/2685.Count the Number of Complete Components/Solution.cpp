// 题目：2685. 统计完全连通分量的数量（Count the Number of Complete Components）
// 思路：先建无向邻接表，再 DFS 每个连通分量，同时统计顶点数 a 与度数之和 b；完全连通分量满足 b = a*(a-1)（每条边被两端各数一次）。
// 时间复杂度：O(n + E)，DFS 与建图各扫一遍；空间复杂度：O(n + E)，邻接表与访问数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countCompleteComponents(int n, vector<vector<int>>& edges) {  // n：顶点数；edges：无向边列表
        vector<vector<int>> g(n);  // g 是邻接表，g[i] 存与 i 相邻的所有顶点
        bool vis[n];  // vis[i] 表示顶点 i 是否已被 DFS 访问过
        memset(vis, false, sizeof(vis));  // 初始都未访问，用 memset 快速清空
        for (auto& e : edges) {  // 遍历每条无向边，把它加到两端点的邻接表里
            int a = e[0], b = e[1];  // 取出这条边的两个端点
            g[a].push_back(b);  // a 的邻居中加入 b
            g[b].push_back(a);  // b 的邻居中加入 a，完成双向建图
        }  // 建图结束
        function<pair<int, int>(int)> dfs = [&](int i) -> pair<int, int> {  // 递归 lambda：返回（分量顶点数, 分量内度数之和）
            vis[i] = true;  // 进入 i 时立即标记已访问，避免重复统计
            int x = 1, y = g[i].size();  // x 先算 i 自己，y 先加上 i 的度数
            for (int j : g[i]) {  // 遍历 i 的所有邻居
                if (!vis[j]) {  // 只递归尚未访问的邻居，保证每个顶点只统计一次
                    auto [a, b] = dfs(j);  // 递归求解邻居所在的那部分
                    x += a;  // 累加顶点数
                    y += b;  // 累加度数（每条边会在两端各贡献 1）
                }  // 分支结束
            }  // 邻居遍历结束
            return make_pair(x, y);  // 返回当前分量的顶点数与度数和
        };  // 结束递归 lambda 的定义
        int ans = 0;  // ans 记录完全连通分量的个数
        for (int i = 0; i < n; ++i) {  // 逐个起点扫描，保证每个连通分量都被处理一次
            if (!vis[i]) {  // 只从未访问的顶点开始新的一轮 DFS
                auto [a, b] = dfs(i);  // 拿到该连通分量的顶点数 a 与度数和 b
                if (a * (a - 1) == b) {  // 完全图的度数和应为 a*(a-1)，相等即为完全连通分量
                    ++ans;  // 计数加一
                }  // 分支结束
            }  // 起点分支结束
        }  // 扫描结束
        return ans;  // 返回完全连通分量的数量
    }  // 方法结束
};  // 类定义结束