# 题目：309. 买卖股票的最佳时机含冷冻期（Best Time to Buy and Sell Stock with Cooldown）
# 思路：记忆化搜索。状态是 (天数, 是否持股)，每天在「不动 / 买入 / 卖出」中取收益最大者，卖出后跳到第 i+2 天。
# 时间复杂度：O(n)，共 2n 个状态；空间复杂度：O(n)，缓存与递归栈。
class Solution:  # LeetCode 约定的题解类
    def maxProfit(self, prices: List[int]) -> int:  # prices 是每日股价，返回最大利润；卖出后必须隔一天才能再买
        @cache  # @cache 自动记忆化，把递归结果缓存起来避免重复计算
        def dfs(i: int, j: int) -> int:  # dfs(i, j)：从第 i 天开始、持股状态为 j（0 空仓 / 1 持股）时的最大收益
            if i >= len(prices):  # 越界判断：卖出后会跳到 i+2，所以 i 可能取到 len(prices)+1
                return 0  # 没有剩余天数，收益为 0
            ans = dfs(i + 1, j)  # 选项一：今天不交易，保持同样的状态进入下一天
            if j:  # 当前持股
                ans = max(ans, prices[i] + dfs(i + 2, 0))  # 卖掉后进入冷冻期，只能从 i+2 天以空仓状态继续
            else:  # 当前空仓
                ans = max(ans, -prices[i] + dfs(i + 1, 1))  # 买入后持仓，明天进入持股状态
            return ans  # 返回较优决策，@cache 会自动记录这次结果

        return dfs(0, 0)  # 从第 0 天、空仓状态出发
