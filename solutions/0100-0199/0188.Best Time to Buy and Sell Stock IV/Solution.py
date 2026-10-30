# 题目：188. 买卖股票的最佳时机 IV（Best Time to Buy and Sell Stock IV）
# 思路：记忆化搜索。dfs(i,j,k) 表示第 i 天、还剩 j 次额度、持仓状态为 k（1 持股 / 0 空仓）时的最大收益。
# 时间复杂度：O(n·k)，每个状态只算一次；空间复杂度：O(n·k)，用于 @cache 缓存所有状态。
class Solution:  # LeetCode 约定的题解类
    def maxProfit(self, k: int, prices: List[int]) -> int:  # k 是最多交易次数，prices 是每日股价
        @cache  # 装饰器：自动把 (i, j, k) 的结果缓存起来，实现记忆化
        def dfs(i: int, j: int, k: int) -> int:  # 形参 k 遮蔽了外层 k，表示「当前是否持股」
            if i >= len(prices):  # 越过最后一天，无法再交易
                return 0  # 递归边界：收益为 0
            ans = dfs(i + 1, j, k)  # 方案一：今天不操作，直接看下一天
            if k:  # 当前持股，只能卖出
                ans = max(ans, prices[i] + dfs(i + 1, j, 0))  # 以今天价格卖出，转为空仓
            elif j:  # 当前空仓且还有交易额度，可以买入
                ans = max(ans, -prices[i] + dfs(i + 1, j - 1, 1))  # 买入支出股价，额度减 1 并转为持股
            return ans  # 返回当前状态的最优收益（由 @cache 负责保存）

        return dfs(0, k, 0)  # 从第 0 天、k 次额度、空仓开始求解
