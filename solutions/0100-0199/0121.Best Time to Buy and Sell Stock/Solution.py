# 题目：121. 买卖股票的最佳时机（Best Time to Buy and Sell Stock）
# 思路：一次遍历，mi 维护历史最低价，每天先用「今天价格 - 历史最低价」更新最大利润，再用今天价格更新最低价。
# 时间复杂度：O(n)，每个价格只遍历一次；空间复杂度：O(1)，只用了两个变量。
class Solution:  # LeetCode 约定的题解类
    def maxProfit(self, prices: List[int]) -> int:  # prices 是每日股价，返回一次买入再卖出能获得的最大利润
        ans, mi = 0, inf  # ans 是最大利润（初值 0 表示可以不交易）；mi 是历史最低价，先设成正无穷
        for v in prices:  # 按时间顺序遍历每一天的价格
            ans = max(ans, v - mi)  # 用「今天卖、历史最低价买」的收益尝试更新答案（第一天 mi 为正无穷，收益为负，不会误判）
            mi = min(mi, v)  # 更新历史最低价，放在后面保证收益计算只用今天及以前的价格
        return ans  # 返回最大利润
