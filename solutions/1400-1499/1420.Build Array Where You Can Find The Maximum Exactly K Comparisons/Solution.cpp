// 题目：1420. 生成数组（Build Array Where You Can Find The Maximum Exactly K Comparisons）
// 核心思路：dp[i][c][j] 表示长度 i、search_cost 为 c、末尾最大值恰为 j 的方案数；新元素不超过 j 时 c 不变，恰为 j 时 c 加一。
// 时间复杂度：O(n·k·m²)，状态数 n·k·m 再乘一层枚举旧最大值；空间复杂度：O(n·k·m)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numOfArrays(int n, int m, int k) {  // n：数组长度；m：元素取值 1..m；k：要求的 search_cost
        if (k == 0) return 0;  // 长度 n≥1 的数组至少发生一次更新，k 为 0 时无解
        int mod = 1e9 + 7;  // 结果对 1e9+7 取模
        using ll = long long;  // 中间乘积用 64 位整数，避免溢出
        vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>>(k + 1, vector<ll>(m + 1)));  // dp[i][c][j]：长度 i、已更新 c 次、末尾最大值恰为 j 的方案数
        for (int i = 1; i <= m; ++i) dp[1][1][i] = 1;  // 长度 1 时第一个元素必定触发一次更新，每个取值各 1 种方案
        for (int i = 2; i <= n; ++i) {  // 长度从 2 递推到 n
            for (int c = 1; c <= min(i, k); ++c) {  // 更新次数不会超过长度 i，也不必超过要求的 k
                for (int j = 1; j <= m; ++j) {  // 枚举当前末尾的最大值 j
                    dp[i][c][j] = (dp[i - 1][c][j] * j) % mod;  // 最大值仍为 j：新元素取 1..j 共 j 种，不新增更新次数
                    for (int j0 = 1; j0 < j; ++j0) {  // 枚举更小的旧最大值 j0（j0 < j）
                        dp[i][c][j] = (dp[i][c][j] + dp[i - 1][c - 1][j0]) % mod;  // 新元素恰为 j 触发一次更新，累加所有 j0 的方案数
                    }  // j0 枚举结束
                }  // j 枚举结束
            }  // c 枚举结束
        }  // i 枚举结束
        ll ans = 0;  // 汇总答案
        for (int i = 1; i <= m; ++i) ans = (ans + dp[n][k][i]) % mod;  // 长度 n、恰 k 次更新的所有末尾最大值方案数之和
        return (int) ans;  // 取模后转回 int 返回
    }  // 方法结束
};  // 题解类定义结束