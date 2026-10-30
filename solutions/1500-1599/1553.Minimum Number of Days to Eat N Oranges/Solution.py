# 题目：1553. 吃掉 N 个橘子的最少天数（Minimum Number of Days to Eat N Oranges）
# 思路：记忆化搜索。每天要么吃 1 个，要么先吃 n%2 个再整除以 2，要么先吃 n%3 个再整除以 3，取三者最优。
# 时间复杂度：O(log^2 n)（状态数约为 O(log n)，每个状态常数级转移）；空间复杂度：O(log n)（缓存存记忆化结果）。
class Solution:  # LeetCode 约定的题解类
    def minDays(self, n: int) -> int:  # n：一开始的橘子总数
        @cache  # 用 cache 自动记忆化，同一 n 只计算一次
        def dfs(n: int) -> int:  # 求吃完 n 个橘子的最少天数
            if n < 2:  # 只剩 0 个或 1 个橘子时，只能一天吃一个
                return n  # 0 个需要 0 天，1 个需要 1 天
            return 1 + min(n % 2 + dfs(n // 2), n % 3 + dfs(n // 3))  # 今天先花几天凑整除，再走"除以 2"或"除以 3"分支，取更省的一条

        return dfs(n)  # 从初始橘子数 n 开始递归求解
