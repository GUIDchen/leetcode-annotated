# 题目：2944. 购买水果需要的最少金币数（Minimum Number of Coins for Fruits）
# 思路：记忆化搜索。dfs(i) 表示从第 i 个水果开始买的最小花费：付掉 prices[i-1] 后，i+1..2i 的水果免费，下一颗要花钱的水果可以是 i+1..2i+1 中的任意一个，取其中最优。
# 时间复杂度：O(n^2)，每个状态枚举 O(n) 个后继；空间复杂度：O(n)，记忆化表加上递归栈。
class Solution:  # LeetCode 约定的题解类
    def minimumCoins(self, prices: List[int]) -> int:  # prices[i-1] 是第 i 个水果的价格，返回买到所有水果所需的最少金币数
        @cache  # @cache 按参数缓存 dfs 的结果，保证每个状态只计算一次
        def dfs(i: int) -> int:  # dfs(i)：从第 i 个水果开始买所需的最少金币
            if i * 2 >= len(prices):  # 2i >= n 时，买下第 i 个水果即可让剩下的水果全部免费
                return prices[i - 1]  # 付第 i 个水果的钱即可覆盖到末尾
            return prices[i - 1] + min(dfs(j) for j in range(i + 1, i * 2 + 2))  # 付第 i 个水果的钱，再在允许的下一颗水果 i+1..2i+1 中取最优

        return dfs(1)  # 从第 1 个水果开始计算，即答案
