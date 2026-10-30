# 题目：123. 买卖股票的最佳时机 III（Best Time to Buy and Sell Stock III）
# 思路：状态机 DP，f1/f2/f3/f4 分别是「第一次买入后、第一次卖出后、第二次买入后、第二次卖出后」的最大收益，逐日滚动更新。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只维护四个状态。
class Solution:  # LeetCode 约定的题解类
    def maxProfit(self, prices: List[int]) -> int:  # prices 是每天的价格，返回最多两笔交易的最大利润
        # 第一次买入，第一次卖出，第二次买入，第二次卖出
        f1, f2, f3, f4 = -prices[0], 0, -prices[0], 0  # 第一天只能买入，故两个买入态是 -prices[0]，两个卖出态（未交易）是 0
        for price in prices[1:]:  # 从第二天开始逐日推进状态
            f1 = max(f1, -price)  # 第一次买入：保持原成本，或今天才第一次买
            f2 = max(f2, f1 + price)  # 第一次卖出：保持原收益，或用今天价格兑现
            f3 = max(f3, f2 - price)  # 第二次买入：拿第一笔的收益在今天买入
            f4 = max(f4, f3 + price)  # 第二次卖出：兑现第二笔交易
        return f4  # f4 即最多两笔交易的最大收益（允许少于两笔）
