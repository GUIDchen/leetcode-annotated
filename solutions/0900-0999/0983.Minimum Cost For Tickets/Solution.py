# 题目：983. 最低票价（Minimum Cost For Tickets）
# 思路：@cache 记忆化 DFS，dfs(i) 表示覆盖 days[i..] 的最小花费；对三种票用 bisect_left 跳到有效期结束后的第一个出行日，取最小值。
# 时间复杂度：O(n log n)，每个状态做 3 次二分；空间复杂度：O(n)，缓存与递归栈。
class Solution:  # LeetCode 约定的题解类
    def mincostTickets(self, days: List[int], costs: List[int]) -> int:  # days 是递增的出行日，costs 是三种票的价格
        @cache  # cache 装饰器：同一个 i 只计算一次
        def dfs(i: int) -> int:  # 从第 i 个出行日开始覆盖的最小花费
            if i >= n:  # 行程已全部覆盖
                return 0  # 不需要再花钱
            ans = inf  # 先设成无穷大，方便取最小值
            for c, v in zip(costs, valid):  # 枚举每种票的价格与有效期
                j = bisect_left(days, days[i] + v)  # 该票覆盖到 days[i] + v，用二分找到第一个未被覆盖的出行日下标
                ans = min(ans, c + dfs(j))  # 在当前票上叠加后续花费，更新最小值
            return ans  # 返回该状态的最优解

        n = len(days)  # n 为出行日总数
        valid = [1, 7, 30]  # 三种通行证的有效天数
        return dfs(0)  # 从第一个出行日开始计算
