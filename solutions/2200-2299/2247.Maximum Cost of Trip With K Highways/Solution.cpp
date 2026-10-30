// 题目：2247. K 条高速公路的最大旅行费用（Maximum Cost of Trip With K Highways，会员题）
// 思路：状压 DP，f[mask][j] 表示已访问城市集合为 mask、当前停在 j 时可获得的最大费用；按 mask 递增枚举并做「去掉 j 从邻居 h 转移」的松弛。
// 时间复杂度：O(2^n * n * deg)，每个状态枚举所有邻边；空间复杂度：O(2^n * n)，DP 表与邻接表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumCost(int n, vector<vector<int>>& highways, int k) {  // n：城市数量；highways：每条高速 [a, b, cost]；k：要求恰好经过的高速条数
        if (k >= n) {  // 走 k 条边需要 k+1 个互不相同的城市，k >= n 时城市不够用，直接无解
            return -1;  // 返回 -1 表示不存在这样的旅行
        }  // 提前返回结束
        vector<pair<int, int>> g[n];  // 邻接表：g[u] 中存 (相邻城市, 该高速的费用)
        for (auto& h : highways) {  // 逐条高速建边
            int a = h[0], b = h[1], cost = h[2];  // 拆出两个端点和这条高速的费用
            g[a].emplace_back(b, cost);  // 无向图先建正向边 a -> b
            g[b].emplace_back(a, cost);  // 反向边费用相同
        }  // 建图完成
        int f[1 << n][n];  // 状压 DP：f[mask][j] = 恰好访问过 mask 这些城市、最后停在 j 时的最大费用
        memset(f, -0x3f, sizeof(f));  // memset 按字节填充，-0x3f 得到约 -1e9 的「负无穷」，表示该状态不可达
        for (int i = 0; i < n; ++i) {  // 初始化：任意单个城市都可以作为起点
            f[1 << i][i] = 0;  // 只含城市 i 的路径还没有走过任何高速，费用为 0
        }  // 起点初始化完毕
        int ans = -1;  // 答案初值 -1，表示暂时无解
        for (int i = 0; i < 1 << n; ++i) {  // 按集合大小天然递增地枚举所有城市集合（mask）
            for (int j = 0; j < n; ++j) {  // 枚举当前所在的城市 j
                if (i >> j & 1) {  // j 必须属于 mask，否则 f[i][j] 没有意义
                    for (auto& [h, cost] : g[j]) {  // C++17 结构化绑定：枚举 j 的邻居 h 与这条边的费用 cost
                        if (i >> h & 1) {  // h 也必须已经在集合里，保证路径不重复经过城市且转移来源合法
                            f[i][j] = max(f[i][j], f[i ^ (1 << j)][h] + cost);  // 把 j 从集合中去掉（i ^ (1<<j)），由停在 h 的状态转移过来并加上这条边的费用
                        }  // 该邻居枚举完
                    }  // j 的邻边全部松弛完毕
                }  // 该 city j 处理完毕
                if (__builtin_popcount(i) == k + 1) {  // 恰好走过 k 条高速意味着恰好经过 k+1 个城市，此时可以更新最终答案
                    ans = max(ans, f[i][j]);  // 取当前集合下所有终点中的最大值
                }  // 该集合统计完毕
            }  // 该 mask 的所有终点枚举完毕
        }  // 所有集合枚举完毕
        return ans;  // 返回最大费用；若从未更新则仍为 -1
    }  // 方法结束
};  // 类定义结束