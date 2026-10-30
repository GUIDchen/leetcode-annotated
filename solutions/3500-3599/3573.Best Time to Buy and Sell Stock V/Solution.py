# 题目：3573. 买卖股票的最佳时机 V（Best Time to Buy and Sell Stock V）
# 思路：动态规划。f[i][j][s] 表示考虑前 i 天、最多完成 j 笔交易、持仓状态为 s（0 空仓 / 1 持有多头 / 2 持有空头）时的最大利润；每天在保持状态、从持仓平仓、开新仓之间取最大值，开新仓时交易数由 j-1 转移而来。
# 时间复杂度：O(n * k)，状态数为 n(k+1)×3，每个状态常数次转移；空间复杂度：O(n * k)。
class Solution:  # LeetCode 约定的题解类
    def maximumProfit(self, prices: List[int], k: int) -> int:  # prices：每天的价格；k：最多允许的交易次数；返回能获得的最大利润
        n = len(prices)  # 开盘天数
        f = [[[0] * 3 for _ in range(k + 1)] for _ in range(n)]  # 三维 DP，f[天数][最多交易次数][持仓状态]，初值全部为 0
        for j in range(1, k + 1):  # 初始化第 0 天：这一天只能开一笔多头或空头仓位
            f[0][j][1] = -prices[0]  # 第 0 天买入多头，利润为负的当日价格
            f[0][j][2] = prices[0]  # 第 0 天空头开仓，先拿到当日价格
        for i in range(1, n):  # 从第 1 天开始逐天递推
            for j in range(1, k + 1):  # 枚举最多可用的交易次数
                f[i][j][0] = max(  # 空仓状态的三种来源取最大值
                    f[i - 1][j][0],  # 保持空仓
                    f[i - 1][j][1] + prices[i],  # 多头今天平仓
                    f[i - 1][j][2] - prices[i],  # 空头今天平仓
                )  # 空仓状态计算结束
                f[i][j][1] = max(f[i - 1][j][1], f[i - 1][j - 1][0] - prices[i])  # 持有多头：继续持有，或从上一次空仓买入开仓
                f[i][j][2] = max(f[i - 1][j][2], f[i - 1][j - 1][0] + prices[i])  # 持有空头：继续持有，或从上一次空仓卖出开仓
        return f[n - 1][k][0]  # 最后一天、最多 k 笔交易且空仓时的利润即为答案
