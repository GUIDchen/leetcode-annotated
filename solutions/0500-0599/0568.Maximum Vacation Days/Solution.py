# 题目：568. 最大休假天数（Maximum Vacation Days）
# 思路：按周做 DP，f[k][j] 表示第 k 周结束待在城市 j 的最大休假天数；来源是上周同城或能直飞 j 的城市，再加本周在该城的休假天数。
# 时间复杂度：O(K·n²)，每周每城枚举来源城市；空间复杂度：O(K·n)，保存整张 DP 表。
class Solution:  # LeetCode 约定的题解类
    def maxVacationDays(self, flights: List[List[int]], days: List[List[int]]) -> int:  # flights 是城市间直飞矩阵，days 是每城每周的休假天数
        n = len(flights)  # n 是城市数量
        K = len(days[0])  # K 是假期总周数
        f = [[-inf] * n for _ in range(K + 1)]  # f[k][j]：第 k 周结束待在城市 j 的最大休假天数，初始为 -inf 表示不可达
        f[0][0] = 0  # 第 0 周开始前只能待在城市 0
        for k in range(1, K + 1):  # 逐周推进
            for j in range(n):  # 枚举本周所在城市
                f[k][j] = f[k - 1][j]  # 先考虑不飞：上周也在 j 城
                for i in range(n):  # 枚举上周所在城市，检查能否直飞到 j
                    if flights[i][j]:  # flights[i][j] 为真表示 i 可以直飞 j（包括原地不动）
                        f[k][j] = max(f[k][j], f[k - 1][i])  # 取上周可达状态中的最大值
                f[k][j] += days[j][k - 1]  # 加上本周在城市 j 的休假天数
        return max(f[-1][j] for j in range(n))  # 最后一周各城市取最大值即为答案
