# 题目：122. 买卖股票的最佳时机 II（Best Time to Buy and Sell Stock II）
# 思路：用 pairwise 取相邻两天的价格，把每一段正差价 max(0, b - a) 累加，等价于反复低买高卖。
# 时间复杂度：O(n)，一趟遍历；空间复杂度：O(1)，只用到常数个中间变量。
class Solution:  # LeetCode 约定的题解类
    def maxProfit(self, prices: List[int]) -> int:  # prices 是每天的价格，返回最大利润
        return sum(max(0, b - a) for a, b in pairwise(prices))  # pairwise 给出相邻对 (a, b)，负差价被 max(0, ...) 归零，只累加上涨部分
