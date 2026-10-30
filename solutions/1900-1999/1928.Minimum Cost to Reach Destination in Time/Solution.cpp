// 题目：1928. 规定时间内到达终点的最小花费（Minimum Cost to Reach Destination in Time）
// 思路：f[i][v] 表示恰好用 i 单位时间到达节点 v 的最小总花费，按时间切面枚举每条边做松弛，最后在终点的各时间切面上取最小。
// 时间复杂度：O(m·E)，m 为 maxTime、E 为边数；空间复杂度：O(m·n)，需要一张 (m+1)×n 的二维表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {  // maxTime：时间上限；edges：无向边；passingFees：每个节点的过路费
        int m = maxTime, n = passingFees.size();  // m 是时间上限，n 是节点个数
        const int inf = 1 << 30;  // 无穷大，表示该状态不可达
        vector<vector<int>> f(m + 1, vector<int>(n, inf));  // f[i][v]：恰好用 i 单位时间到达 v 的最小花费
        f[0][0] = passingFees[0];  // 0 时刻位于起点 0，花费就是起点的过路费
        for (int i = 1; i <= m; ++i) {  // 按时间从小到大逐个切面推进
            for (const auto& e : edges) {  // 每条无向边都尝试做一次松弛
                int x = e[0], y = e[1], t = e[2];  // 边的两个端点 x、y 以及这条边耗时 t
                if (t <= i) {  // 边耗时不超过当前时间，才有可能从更早的时刻走过来
                    f[i][x] = min(f[i][x], f[i - t][y] + passingFees[x]);  // 从 y 出发经这条边在 i 时刻到达 x
                    f[i][y] = min(f[i][y], f[i - t][x] + passingFees[y]);  // 反向同理：从 x 在 i 时刻到达 y
                }
            }
        }
        int ans = inf;  // 记录终点在所有时间切面上的最小花费
        for (int i = 1; i <= m; ++i) {  // 枚举不超过 maxTime 的每个到达时刻
            ans = min(ans, f[i][n - 1]);  // 用终点 n-1 在该时刻的花费更新答案
        }
        return ans == inf ? -1 : ans;  // 所有切面都不可达则返回 -1
    }
};
