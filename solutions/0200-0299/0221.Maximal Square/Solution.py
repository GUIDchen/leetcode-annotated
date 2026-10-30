# 题目：221. 最大正方形（Maximal Square）
# 核心思路：dp[i+1][j+1] 表示以 (i,j) 为右下角的最大全 '1' 正方形边长，等于左、上、左上三个值的最小值加一。
# 时间复杂度：O(mn)，每个格子算一次；空间复杂度：O(mn)，dp 表多开一圈边界。
class Solution:  # LeetCode 约定的题解类
    def maximalSquare(self, matrix: List[List[str]]) -> int:  # 求全为 '1' 的最大正方形面积
        m, n = len(matrix), len(matrix[0])  # 行数 m 与列数 n
        dp = [[0] * (n + 1) for _ in range(m + 1)]  # dp[i+1][j+1] 是以 (i,j) 为右下角的最大正方形边长；多开一圈 0 作边界哨兵
        mx = 0  # mx 记录出现过的最大边长
        for i in range(m):  # 逐行扫描
            for j in range(n):  # 逐列扫描
                if matrix[i][j] == '1':  # 只有当前位置是 '1' 才可能扩展出正方形
                    dp[i + 1][j + 1] = min(dp[i][j + 1], dp[i + 1][j], dp[i][j]) + 1  # 左、上、左上三个方向的最小边长加一，就是当前格的最大边长
                    mx = max(mx, dp[i + 1][j + 1])  # 更新全局最大边长
        return mx * mx  # 题目要求面积，返回最大边长的平方
