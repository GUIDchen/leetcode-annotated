# 题目：1467. 两个盒子中球的颜色数相同的概率（Probability of a Two Boxes Having The Same Number of Distinct Balls）
# 核心思路：组合数 + 记忆化搜索。按颜色逐个决定放几个球进第一个盒子，同时维护还需放的球数 j 与「颜色数差」diff，合法方案数除以总分配数 C(2n, n) 即为概率。
# 时间复杂度：O(k·n·k·maxBall)，状态数 k×n×2k；空间复杂度：O(k·n·k)，记忆化表的大小。
class Solution:  # LeetCode 约定的题解类
    def getProbability(self, balls: List[int]) -> float:  # balls[i] 是第 i 种颜色的球数，返回值是颜色数相同的概率
        @cache  # 用 functools.cache 做记忆化，同一状态只算一次
        def dfs(i: int, j: int, diff: int) -> float:  # i：当前颜色下标；j：第一个盒子还差的球数；diff：当前颜色数差
            if i >= k:  # 所有颜色都已分配完
                return 1 if j == 0 and diff == 0 else 0  # 球数刚好分完且颜色数差为 0 才算一种合法方案
            if j < 0:  # 第一个盒子放超了，该分支无效
                return 0  # 无解，返回 0
            ans = 0  # 累加当前状态的方案数
            for x in range(balls[i] + 1):  # 枚举第 i 种颜色放进第一个盒子的个数 x
                y = 1 if x == balls[i] else (-1 if x == 0 else 0)  # 全放 A 记 +1，全放 B 记 -1，两边都有记 0
                ans += dfs(i + 1, j - x, diff + y) * comb(balls[i], x)  # 子问题方案数乘以该颜色的选择数 C(balls[i], x)
            return ans  # 返回当前状态的方案数

        n = sum(balls) >> 1  # 每个盒子要装的球数 n
        k = len(balls)  # 颜色种数，dfs 中用作终止条件
        return dfs(0, n, 0) / comb(n << 1, n)  # 合法方案数 / 总分配数 C(2n, n) 即概率
