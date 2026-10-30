# 题目：174. 地下城游戏（Dungeon Game）
# 思路：从右下角倒推到左上角，dp[i][j] 表示进入 (i,j) 前至少需要的生命值：dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j])。
# 时间复杂度：O(mn)，每个格子算一次；空间复杂度：O(mn)，需要一张 dp 表。
class Solution:  # LeetCode 约定的题解类
    def calculateMinimumHP(self, dungeon: List[List[int]]) -> int:  # 求骑士进入左上角时至少需要多少初始生命值才能走到右下角
        m, n = len(dungeon), len(dungeon[0])  # 行数与列数
        dp = [[inf] * (n + 1) for _ in range(m + 1)]  # 多开一行一列作为哨兵，先全部初始化为正无穷
        dp[m][n - 1] = dp[m - 1][n] = 1  # 终点右方与下方的哨兵设为 1：到达终点后只需 1 点生命
        for i in range(m - 1, -1, -1):  # 从最后一行往上推（range 的步长为 -1）
            for j in range(n - 1, -1, -1):  # 从最后一列往左推
                dp[i][j] = max(1, min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j])  # 取右、下两条路中需求较小的一个，减去本格消耗；生命至少为 1
        return dp[0][0]  # 左上角的值就是答案
