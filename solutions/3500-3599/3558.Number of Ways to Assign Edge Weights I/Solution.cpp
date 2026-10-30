// 3558. 给边赋权值的方案数 I / Number of Ways to Assign Edge Weights I
// 核心思路：每条边权取 1 或 2，从根结点 1 到最深结点的路径有 d 条边，只要路径上出现奇数个权值 1，路径和就是奇数，故方案数为 2^(d-1)。
// 复杂度：时间 O(n)，空间 O(n)
class Solution {  // 定义解题类
public:  // 公有接口
    int assignEdgeWeights(vector<vector<int>>& edges) {  // 返回使 1 到最深结点路径和为奇数的赋权方案数
        int n = edges.size() + 1;  // 结点数等于边数加一
        vector<vector<int>> g(n + 1);  // 邻接表，下标从 1 开始

        for (auto& e : edges) {  // 遍历每条边建立无向图
            int u = e[0];  // 边的一个端点
            int v = e[1];  // 边的另一个端点
            g[u].push_back(v);  // u 的邻居列表中加入 v
            g[v].push_back(u);  // v 的邻居列表中加入 u
        }  // 结束建图

        auto dfs = [&](this auto&& dfs, int i, int fa) -> int {  // 递归求以 i 为根、父结点为 fa 时的最大深度
            int res = 0;  // 记录子结点方向的最大深度
            for (int j : g[i]) {  // 枚举结点 i 的邻居
                if (j != fa) {  // 跳过父结点，避免走回头路
                    res = max(res, dfs(j, i) + 1);  // 子方向深度加一后取最大值
                }  // 结束子结点判断
            }  // 结束邻居枚举
            return res;  // 返回最大深度
        };  // 结束深度递归 lambda

        return pow(2, dfs(1, 0) - 1, 1000000007);  // 深度为 d 时有 d 条边，方案数为 2^(d-1)，模 1e9+7
    }  // 结束 assignEdgeWeights

private:  // 私有辅助函数
    long long pow(long long a, int n, int mod) {  // 快速幂：求 a^n mod mod
        long long res = 1;  // 幂的累乘结果，初始为 1
        while (n > 0) {  // 指数未减到 0 时循环
            if (n & 1) {  // 指数的当前最低位为 1
                res = res * a % mod;  // 把 a 累乘进结果并取模
            }  // 结束最低位判断
            a = a * a % mod;  // 底数平方并取模
            n >>= 1;  // 指数右移一位
        }  // 结束循环
        return res;  // 返回 a^n mod mod
    }  // 结束 pow
};  // 结束类定义
