// 题目：1615. 最大网络秩（Maximal Network Rank）
// 思路：先统计每个城市的度数 cnt，再用邻接矩阵 g 标记直连关系；枚举所有城市对，秩 = cnt[a] + cnt[b] - g[a][b]。
// 时间复杂度：O(n^2 + m)，m 为道路条数；空间复杂度：O(n^2)，主要开销是邻接矩阵。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {  // n：城市个数；roads：道路端点列表
        int cnt[n];  // cnt[i] 表示与城市 i 直接相连的道路条数（度数）
        int g[n][n];  // 邻接矩阵：g[a][b] == 1 表示 a、b 之间有一条直接道路
        memset(cnt, 0, sizeof(cnt));  // 度数数组整体清零，避免残留脏值
        memset(g, 0, sizeof(g));  // 邻接矩阵整体清零
        for (auto& r : roads) {  // 遍历每条道路
            int a = r[0], b = r[1];  // 取出道路的两个端点
            g[a][b] = g[b][a] = 1;  // 无向图，矩阵对称置 1，供后面减去重复道路
            ++cnt[a];  // 端点 a 的度数加一
            ++cnt[b];  // 端点 b 的度数加一
        }
        int ans = 0;  // 记录枚举过程中的最大网络秩
        for (int a = 0; a < n; ++a) {  // 枚举城市对中的第一个城市
            for (int b = a + 1; b < n; ++b) {  // 只枚举 b > a，避免同一对城市被算两次
                ans = max(ans, cnt[a] + cnt[b] - g[a][b]);  // 度数之和再减去被重复计入的那条公共道路
            }
        }
        return ans;  // 返回最大网络秩
    }
};