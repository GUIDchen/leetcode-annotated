# 题目：1223. 掷骰子模拟（Dice Roll Simulation）
# 思路：@cache 记忆化搜索，状态为「已掷次数 i、上一次点数 j、j 已连续出现次数 x」，枚举下一个点数并把各分支方案数累加取模。
# 时间复杂度：O(n × 6 × 15)，状态数约 90n、每状态枚举 6 个点数；空间复杂度：O(n × 6 × 15)，即缓存表大小。
class Solution:  # LeetCode 约定的题解类
    def dieSimulator(self, n: int, rollMax: List[int]) -> int:  # n：要掷的总次数；rollMax[i]：点数 i+1 最多能连续出现的次数
        @cache  # @cache 记忆化：相同的 (i, j, x) 只计算一次
        def dfs(i, j, x):  # i 已掷次数、j 上一次点数（0 表示还没掷）、x 该点数已连续出现的次数
            if i >= n:  # 递归出口：n 次已经全部掷完
                return 1  # 这条完整序列合法，计 1 种方案
            ans = 0  # 累计当前状态的方案数
            for k in range(1, 7):  # 枚举下一次可能掷出的点数 1..6
                if k != j:  # 点数换了：连续段结束，不再受 rollMax 约束
                    ans += dfs(i + 1, k, 1)  # 换点数后连续次数重置为 1，递归到下一层
                elif x < rollMax[j - 1]:  # 点数没变，检查是否还在该点数的连续次数上限内
                    ans += dfs(i + 1, j, x + 1)  # 还在上限内，接着掷同一个点数，连续次数 +1
            return ans % (10**9 + 7)  # 所有分支求和后按题目要求对 1e9+7 取模

        return dfs(0, 0, 0)  # 从「第 0 次、没有上一次点数、连续 0 次」开始搜索，结果即答案
