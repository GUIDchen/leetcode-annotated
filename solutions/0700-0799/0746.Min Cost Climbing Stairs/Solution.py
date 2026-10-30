# 题目：746. 使用最小花费爬楼梯（Min Cost Climbing Stairs）
# 核心思路：记忆化搜索，dfs(i) = cost[i] + min(dfs(i + 1), dfs(i + 2))，i 越过楼顶时返回 0，答案是 dfs(0) 与 dfs(1) 的较小值。
# 时间复杂度：O(n)，@cache 保证每个下标只算一次；空间复杂度：O(n)，缓存与递归栈的深度。
class Solution:  # LeetCode 约定的题解类
    def minCostClimbingStairs(self, cost: List[int]) -> int:  # cost[i] 是踩上第 i 阶需要支付的费用
        @cache  # 记忆化装饰器：同一个 i 只真正计算一次，把指数级搜索降为线性
        def dfs(i: int) -> int:  # 返回从第 i 阶出发走到楼顶所需的最小花费
            if i >= len(cost):  # 下标越过最后一级台阶，说明已经站上楼顶
                return 0  # 楼顶不再产生费用，这是递归出口
            return cost[i] + min(dfs(i + 1), dfs(i + 2))  # 付当前阶的费用，再在走一阶与走两阶里选更省的

        return min(dfs(0), dfs(1))  # 起点可以是第 0 阶或第 1 阶，取两种起步方式中更省的
