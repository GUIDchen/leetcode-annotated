# 题目：764. 最大加号标志（Largest Plus Sign）
# 思路：以每个格子为中心做四方向「连续可用长度」的 DP，一次双向扫描同时更新左右上下，最后取所有中心臂长的最大值。
# 时间复杂度：O(n^2)，每个格子常数次更新；空间复杂度：O(n^2)，dp 矩阵。
class Solution:  # LeetCode 约定的题解类
    def orderOfLargestPlusSign(self, n: int, mines: List[List[int]]) -> int:  # n 是边长，mines 是地雷坐标
        dp = [[n] * n for _ in range(n)]  # dp[i][j] 表示以 (i,j) 为中心的臂长候选上界，先全部填 n
        for x, y in mines:  # 遍历所有地雷坐标
            dp[x][y] = 0  # 地雷格子臂长置 0，不能参与构成加号
        for i in range(n):  # 逐行、逐列作为中心线进行扫描
            left = right = up = down = 0  # 四个方向上当前的连续可用长度
            for j, k in zip(range(n), reversed(range(n))):  # j 从左往右、k 从右往左，一次循环完成双向 DP
                left = left + 1 if dp[i][j] else 0  # 行内自左向右的连续长度，遇 0 清零
                right = right + 1 if dp[i][k] else 0  # 行内自右向左的连续长度
                up = up + 1 if dp[j][i] else 0  # 列内自上而下的连续长度
                down = down + 1 if dp[k][i] else 0  # 列内自下而上的连续长度
                dp[i][j] = min(dp[i][j], left)  # 用左臂长度收紧该中点的臂长
                dp[i][k] = min(dp[i][k], right)  # 用右臂长度收紧该中点的臂长
                dp[j][i] = min(dp[j][i], up)  # 用上臂长度收紧该中点的臂长
                dp[k][i] = min(dp[k][i], down)  # 用下臂长度收紧该中点的臂长
        return max(max(v) for v in dp)  # 所有格子臂长中的最大值即答案
