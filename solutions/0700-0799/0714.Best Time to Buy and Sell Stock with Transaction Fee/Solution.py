# 题目：714. 买卖股票的最佳时机含手续费（Best Time to Buy and Sell Stock with Transaction Fee）
# 核心思路：记忆化搜索。状态为「第 i 天 + 当前是否持股」，每天要么不操作、要么买入（空仓转持股）、要么卖出（持股转空仓并付手续费），取收益最大者。
# 时间复杂度：O(n)，每个状态只计算一次（共 2n 个状态）；空间复杂度：O(n)，记忆化缓存与递归栈深度均为 O(n)。
class Solution:  # LeetCode 约定的题解类
    def maxProfit(self, prices: List[int], fee: int) -> int:  # prices 是每日股价，fee 是每笔交易的固定手续费，返回能获得的最大利润
        @cache  # 装饰器：自动缓存 dfs(i, j) 的结果，实现记忆化
        def dfs(i: int, j: int) -> int:  # 递归函数：从第 i 天、持股状态 j（1 持股 / 0 空仓）出发能获得的最大收益
            if i >= len(prices):  # 已经越过最后一天，不能再交易
                return 0  # 递归边界：收益为 0
            ans = dfs(i + 1, j)  # 选择「今天不操作」，状态保持不变
            if j:  # 当前持股，只能考虑卖出（或继续持有）
                ans = max(ans, prices[i] + dfs(i + 1, 0) - fee)  # 卖出：拿到今日股价并付手续费，明天变为空仓
            else:  # 当前空仓，只能考虑买入
                ans = max(ans, -prices[i] + dfs(i + 1, 1))  # 买入：付出今日股价，明天变为持股
            return ans  # 返回两种选择中的较大收益

        return dfs(0, 0)  # 从第 0 天、空仓状态开始求解
