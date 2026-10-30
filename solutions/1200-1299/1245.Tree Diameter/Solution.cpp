// 题目：1245. 树的直径（Tree Diameter）
// 思路：两次 DFS —— 先任取一点求出最远点 a，再从 a 出发求最远距离，该距离就是树的直径（边数）。
// 时间复杂度：O(n)，两次遍历每条边各走一遍；空间复杂度：O(n)，邻接表与 O(n) 递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法入口
    int treeDiameter(vector<vector<int>>& edges) {  // edges 是树的 n-1 条无向边，返回直径（边数）
        int n = edges.size() + 1;  // 边数加一就是节点数
        vector<int> g[n];  // 邻接表：g[u] 保存 u 的所有邻居
        for (auto& e : edges) {  // 逐条边建图
            int a = e[0], b = e[1];  // 取出该边的两个端点
            g[a].push_back(b);  // 把 b 加入 a 的邻居列表
            g[b].push_back(a);  // 无向边，方向反过来也要加一次
        }
        int ans = 0, a = 0;  // ans：当前最远距离；a：最远距离对应的端节点
        auto dfs = [&](this auto&& dfs, int i, int fa, int t) -> void {  // 递归 lambda（C++23 deducing this 让 lambda 调用自身），i 为当前点、fa 为父节点、t 为距起点的距离
            for (int j : g[i]) {  // 枚举当前点的所有邻居
                if (j != fa) {  // 不回头访问父节点，避免在树上绕圈
                    dfs(j, i, t + 1);  // 递归进入子节点，距离加一
                }
            }
            if (ans < t) {  // 后序位置：用当前深度尝试更新最远距离
                ans = t;  // 记录更远的距离
                a = i;  // 记录该端点，供第二次搜索作为起点
            }
        };
        dfs(0, -1, 0);  // 第一次 DFS：从任意点 0 出发，找到最远点 a
        dfs(a, -1, 0);  // 第二次 DFS：从 a 出发，能走到的最远距离就是直径
        return ans;  // 返回直径（边数）
    }
};  // 类定义结束
