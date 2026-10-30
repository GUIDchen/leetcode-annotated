// 题目：174. 地下城游戏（Dungeon Game）
// 思路：从右下角往左上角做 DP，dp[i][j] 表示「进入 (i,j) 之前至少需要的生命值」：dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j])。
// 时间复杂度：O(mn)，每个格子算一次；空间复杂度：O(mn)，需要一张 dp 表。
class Solution {  // LeetCode 约定的题解类
public:  // 对外接口
    int calculateMinimumHP(vector<vector<int>>& dungeon) {  // 求骑士进入左上角时至少需要多少初始生命值才能走到右下角
        int m = dungeon.size(), n = dungeon[0].size();  // 行数 m 与列数 n
        int dp[m + 1][n + 1];  // dp 表多开一行一列，用来放置边界哨兵
        memset(dp, 0x3f, sizeof dp);  // 先全部置为极大值 0x3f3f3f3f，表示「该方向走不通」
        dp[m][n - 1] = dp[m - 1][n] = 1;  // 终点右方与下方的哨兵设为 1：走到终点后只需保留 1 点生命
        for (int i = m - 1; ~i; --i) {  // 从最后一行往上推（~i 为真等价于 i >= 0，是常用的逆序写法）
            for (int j = n - 1; ~j; --j) {  // 从最后一列往左推
                dp[i][j] = max(1, min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j]);  // 取右、下两条路中需求较小的一个，减去本格消耗（负数则回血）；生命至少为 1
            }  // 内层循环结束
        }  // 外层循环结束
        return dp[0][0];  // 左上角的值就是从起点出发所需的最小初始生命值
    }  // 方法结束
};  // 类定义结束