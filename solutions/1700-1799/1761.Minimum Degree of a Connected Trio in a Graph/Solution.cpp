// 题目：1761. 一个图中连通三元组的最小度数（Minimum Degree of a Connected Trio in a Graph）
// 思路：邻接矩阵存图并统计度数，三重循环枚举 i<j<k，三点两两相连时用三度之和减 6（组内 3 条边各贡献 2 个度）更新答案。
// 时间复杂度：O(n^3)，枚举所有三元组；空间复杂度：O(n^2)，邻接矩阵占 O(n^2)，度数数组占 O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minTrioDegree(int n, vector<vector<int>>& edges) {  // n：顶点数（编号 1..n）；edges：边列表
        bool g[n][n];  // 邻接矩阵，g[u][v] 为 true 表示 u 与 v 之间有边
        memset(g, 0, sizeof g);  // 全部初始化为无边
        int deg[n];  // 记录每个顶点的度数
        memset(deg, 0, sizeof deg);  // 度数清零
        for (auto& e : edges) {  // 遍历每条边
            int u = e[0] - 1, v = e[1] - 1;  // 题目编号从 1 开始，减一换算成 0 开始的下标
            g[u][v] = g[v][u] = true;  // 无向图，两个方向都要标记为相连
            deg[u]++, deg[v]++;  // 两个端点的度数各加一
        }
        int ans = INT_MAX;  // 记录最小度数，初值为无穷大
        for (int i = 0; i < n; ++i) {  // 枚举三元组的第一个顶点
            for (int j = i + 1; j < n; ++j) {  // 第二个顶点，保证 i < j < k 从而不重不漏
                if (g[i][j]) {  // i 与 j 必须相连
                    for (int k = j + 1; k < n; ++k) {  // 第三个顶点
                        if (g[j][k] && g[i][k]) {  // j-k 与 i-k 也相连，三点构成连通三元组
                            ans = min(ans, deg[i] + deg[j] + deg[k] - 6);  // 减去组内 3 条边的 6 个度数，得到对外连接数
                        }
                    }
                }
            }
        }
        return ans == INT_MAX ? -1 : ans;  // 没找到三元组返回 -1，否则返回最小度数
    }
};