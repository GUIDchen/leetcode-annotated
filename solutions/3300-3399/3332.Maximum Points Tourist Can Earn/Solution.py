# 题目：3332. 旅客可以得到的最多点数（Maximum Points Tourist Can Earn）
# 思路：按天做动态规划，f[i][j] 表示第 i 天结束停在第 j 个城市的最大得分；转移时枚举前一天的城市 h，留在原地取 stayScore，换城市取 travelScore。
# 时间复杂度：O(k·n^2)，三重循环；空间复杂度：O(k·n)，dp 表大小。
class Solution:  # LeetCode 约定的题解类
    def maxScore(  # n 是城市数，k 是天数，两个得分表分别是停留与移动的收益
        self, n: int, k: int, stayScore: List[List[int]], travelScore: List[List[int]]  # 参数换行只是为满足行宽限制，含义与上一行相同
    ) -> int:  # 返回最大点数
        f = [[-inf] * n for _ in range(k + 1)]  # f[i][j]：第 i 天在第 j 个城市的最大得分，先全部初始化为负无穷
        f[0] = [0] * n  # 第 0 天还没出发，任何城市得分都是 0，作为递推起点
        for i in range(1, k + 1):  # 逐天递推
            for j in range(n):  # 枚举第 i 天结束时的城市 j
                for h in range(n):  # 枚举前一天所在的城市 h
                    f[i][j] = max(  # 从所有来源城市中取最优值
                        f[i][j],  # 保留已有的较优解
                        f[i - 1][h]  # 前一天在 h 城市的得分
                        + (stayScore[i - 1][j] if j == h else travelScore[h][j]),  # h == j 时留在原地拿 stayScore，否则移动拿 travelScore
                    )  # max 调用结束
        return max(f[k])  # 第 k 天可在任意城市收尾，取全局最大值
