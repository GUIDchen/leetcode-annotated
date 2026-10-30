// 题目：2959. 关闭分部的可行集合数目（Number of Possible Sets of Closing Branches）
// 思路：n 很小，用二进制掩码枚举所有保留集合，每种集合只保留两端都在集合内的道路并跑 Floyd 求最短路，若所有保留点对距离都不超过 maxDistance 则该方案可行。
// 时间复杂度：O(2^n * n^3)，枚举 2^n 种集合、每种做一次 Floyd；空间复杂度：O(n^2)，邻接矩阵 g。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfSets(int n, int maxDistance, vector<vector<int>>& roads) {  // n 为分部数，maxDistance 为任意两保留分部的最远距离上限，roads 为道路列表
        int ans = 0;  // 记录可行方案数
        for (int mask = 0; mask < 1 << n; ++mask) {  // 用二进制掩码枚举保留哪些分部，mask 的第 k 位为 1 表示保留分部 k
            int g[n][n];  // 变长数组作为本次枚举的邻接矩阵
            memset(g, 0x3f, sizeof(g));  // 初始化为很大的值 0x3f3f3f3f，表示两点暂时不可达
            for (auto& e : roads) {  // 遍历每条道路
                int u = e[0], v = e[1], w = e[2];  // 道路连接 u、v，长度为 w
                if ((mask >> u & 1) & (mask >> v & 1)) {  // 只有两端分部都被保留时才允许使用这条道路
                    g[u][v] = min(g[u][v], w);  // 无向边取较短权重，兼容重边
                    g[v][u] = min(g[v][u], w);  // 反方向做同样的赋值
                }  // 保留条件判断结束
            }  // 建图循环结束
            for (int k = 0; k < n; ++k) {  // Floyd 的中间点 k
                if (mask >> k & 1) {  // 中间点必须属于被保留的分部
                    g[k][k] = 0;  // 自己到自己的距离为 0
                    for (int i = 0; i < n; ++i) {  // 枚举起点 i
                        for (int j = 0; j < n; ++j) {  // 枚举终点 j
                            g[i][j] = min(g[i][j], g[i][k] + g[k][j]);  // 用经过 k 的路径松弛 i 到 j 的最短路
                        }  // 终点循环结束
                    }  // 起点循环结束
                }  // 中间点分支结束
            }  // Floyd 循环结束
            int ok = 1;  // 标记该保留集合是否可行
            for (int i = 0; i < n && ok == 1; ++i) {  // 检查所有保留点对，一旦发现不可行就提前结束
                for (int j = 0; j < n && ok == 1; ++j) {  // 枚举终点 j，同样可提前结束
                    if ((mask >> i & 1) & (mask >> j & 1) && g[i][j] > maxDistance) {  // 两端都被保留且最短路超过上限，说明该集合不可行
                        ok = 0;  // 标记为不可行
                    }  // 判断结束
                }  // 终点循环结束
            }  // 起点循环结束
            ans += ok;  // 可行则方案数加一（ok 为 0 或 1）
        }  // 掩码枚举循环结束
        return ans;  // 返回可行方案总数
    }  // 方法体结束
};  // 题解类结束