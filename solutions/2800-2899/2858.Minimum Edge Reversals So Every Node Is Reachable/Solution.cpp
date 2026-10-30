// 题目：2858. 可以到达每一个节点的最少边反转次数（Minimum Edge Reversals So Every Node Is Reachable）
// 思路：把有向边建成带权无向图（原方向权值 1、反方向 -1），先 DFS 求出以 0 为根的答案，再换根 DP 推出每个节点的答案。
// 复杂度：时间 O(n + m)，两次 DFS 各遍历每条边一次；空间 O(n + m)，邻接表加递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {  // n：节点数；edges：有向边，要求选定根后能到达所有节点
        vector<pair<int, int>> g[n];  // 邻接表 g[i] 存 (邻居, 权值)：1 表示沿原边，-1 表示需要反转
        vector<int> ans(n);  // ans[i] 保存以 i 为根时需要反转的边数
        for (auto& e : edges) {  // 把每条有向边拆成两条带权无向边
            int x = e[0], y = e[1];  // 取出边的起点与终点
            g[x].emplace_back(y, 1);  // 原方向 x→y，权值 1，不需要反转
            g[y].emplace_back(x, -1);  // 反方向 y→x 要反转，权值记为 -1
        }
        function<void(int, int)> dfs = [&](int i, int fa) {  // 第一次 DFS：算出以 0 号节点为根时的反转次数
            for (auto& [j, k] : g[i]) {  // 遍历当前节点的所有邻边，j 是邻居，k 是边权
                if (j != fa) {  // 跳过父节点，防止沿树边往回走
                    ans[0] += k < 0;  // 权值为 -1 说明这条边方向反了，需要额外反转一次
                    dfs(j, i);  // 递归进入子树继续统计
                }
            }
        };
        function<void(int, int)> dfs2 = [&](int i, int fa) {  // 第二次 DFS：换根，用父节点的答案推出子节点的答案
            for (auto& [j, k] : g[i]) {  // 遍历当前节点的所有邻边
                if (j != fa) {  // 只处理父节点之外的子节点
                    ans[j] = ans[i] + k;  // 关键递推：沿原边翻根代价不变，反向边则答案减 1
                    dfs2(j, i);  // 继续向子树传播答案
                }
            }
        };
        dfs(0, -1);  // 先求 0 号节点的答案，-1 表示没有父节点
        dfs2(0, -1);  // 再从根出发把答案扩散到整棵树
        return ans;  // 返回每个节点的最少反转次数
    }
};
