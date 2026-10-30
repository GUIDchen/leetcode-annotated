# 3466. 最大硬币收集量 / Maximum Coin Collection
# 核心思路：记忆化搜索，状态为（列号、当前泳道、剩余换道次数），每步可在本列取币或换道后再取，取最大值。
# 复杂度：时间 O(n)，空间 O(n)（状态数 3n 个，每状态 O(1) 转移）。
class Solution:  # 定义题解类
    def maxCoins(self, lane1: List[int], lane2: List[int]) -> int:  # 返回最多换道两次能收集到的最多硬币数
        @cache  # 用 cache 缓存递归结果
        def dfs(i: int, j: int, k: int) -> int:  # 递归函数：从第 i 列第 j 条泳道出发、剩余 k 次换道时的最大收益
            if i >= n:  # 已经越过最后一列
                return 0  # 无法继续收集硬币
            x = lane1[i] if j == 0 else lane2[i]  # 当前格子的硬币数
            ans = max(x, dfs(i + 1, j, k) + x)  # 两种选择：只取当前格，或取当前格后沿本泳道继续
            if k > 0:  # 还有剩余换道次数
                ans = max(ans, dfs(i + 1, j ^ 1, k - 1) + x)  # 换到另一条泳道并取当前格
                ans = max(ans, dfs(i, j ^ 1, k - 1))  # 先换道，再在同一列决定是否取币
            return ans  # 返回该状态的最优值

        n = len(lane1)  # 列数
        ans = -inf  # 全局答案，初始化为负无穷
        for i in range(n):  # 枚举起点列
            ans = max(ans, dfs(i, 0, 2))  # 从第 0 条泳道、剩余 2 次换道开始搜索
        return ans  # 返回最大硬币收集量
