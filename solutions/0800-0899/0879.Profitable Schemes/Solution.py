# 题目：879. 盈利计划（Profitable Schemes）
# 核心思路：三维记忆化搜索，状态为（计划下标，已用人数，已赚利润封顶到 minProfit），每个计划做「选 / 不选」的决策并累加方案数。
# 时间复杂度：O(m * n * minProfit)，每个状态只算一次；空间复杂度：O(m * n * minProfit)，@cache 缓存全部状态。
class Solution:  # LeetCode 约定的题解类
    def profitableSchemes(  # 参数分行书写：n 可用人数、minProfit 最低利润、group 各计划所需人数、profit 各计划利润
        self, n: int, minProfit: int, group: List[int], profit: List[int]  # 逐个列出参数及其类型注解
    ) -> int:  # 返回值是满足条件的方案数
        @cache  # 记忆化装饰器：相同的 (i, j, k) 只计算一次
        def dfs(i: int, j: int, k: int) -> int:  # i 当前计划下标，j 已用人数，k 已赚利润（封顶到 minProfit）
            if i >= len(group):  # 所有计划都已决策完
                return 1 if k == minProfit else 0  # 利润正好达到 minProfit 算一种方案，否则不算
            ans = dfs(i + 1, j, k)  # 不选当前计划：人数与利润都不变
            if j + group[i] <= n:  # 人数够用才能选当前计划
                ans += dfs(i + 1, j + group[i], min(k + profit[i], minProfit))  # 选它：人数增加，利润累加并封顶到 minProfit
            return ans % (10**9 + 7)  # 取模后返回方案数，防止整数溢出

        return dfs(0, 0, 0)  # 从第 0 个计划、0 人、0 利润开始搜索
