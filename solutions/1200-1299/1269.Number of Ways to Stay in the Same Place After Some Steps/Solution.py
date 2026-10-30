class Solution:  # LeetCode 约定的题解类
    def numWays(self, steps: int, arrLen: int) -> int:  # steps：总步数；arrLen：数组长度，位置合法范围是 [0, arrLen-1]
        @cache  # @cache 自动记忆化，同一个 (i, j) 只计算一次
        def dfs(i, j):  # dfs(i, j)：当前位置 i，还剩 j 步
            if i > j or i >= arrLen or i < 0 or j < 0:  # 越界，或剩余步数不足以回到 0 号位置时无解
                return 0  # 这种状态贡献 0 种方案
            if i == 0 and j == 0:  # 所有步走完且正好停在 0 号位置
                return 1  # 这是一种合法走法
            ans = 0  # 累加三种走法的方案数
            for k in range(-1, 2):  # 枚举 -1 左移、0 原地、+1 右移
                ans += dfs(i + k, j - 1)  # 累加子状态的方案数
                ans %= mod  # 每次累加后取模，防止数值过大
            return ans  # 返回当前状态的方案数（由 @cache 缓存）

        mod = 10**9 + 7  # 取模常量；写在 dfs 之后，但调用时已经存在
        return dfs(0, steps)  # 从位置 0、剩余 steps 步开始搜索
