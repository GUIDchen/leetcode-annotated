# 题目：3317. 安排活动的方案数（Find the Number of Possible Ways for an Event）
# 核心思路：f[i][j] 表示把前 i 位表演者安排到恰好 j 个非空节目（节目有编号）的方案数，f[i][j] = f[i-1][j]*j + f[i-1][j-1]*(x-j+1)；最后对每个 j 乘上给这些节目打分的 y^j 再求和。
# 时间复杂度：O(n·x)；空间复杂度：O(n·x)。
class Solution:  # LeetCode 约定的题解类
    def numberOfWays(self, n: int, x: int, y: int) -> int:  # n：表演者人数；x：节目数；y：每个节目的分数取值范围 [1, y]
        mod = 10**9 + 7  # 按题目要求对 1e9+7 取模
        f = [[0] * (x + 1) for _ in range(n + 1)]  # f[i][j]：前 i 位表演者恰好占用 j 个非空节目的方案数
        f[0][0] = 1  # 0 个人、0 个节目，空方案算 1 种
        for i in range(1, n + 1):  # 逐个加入表演者
            for j in range(1, x + 1):  # 枚举当前被占用的节目个数
                f[i][j] = (f[i - 1][j] * j + f[i - 1][j - 1] * (x - (j - 1))) % mod  # 加入已有的 j 个节目之一（j 种），或新开一个节目（还剩 x-(j-1) 个可选）
        ans, p = 0, 1  # ans 累加答案；p 用来维护 y 的 j 次幂
        for j in range(1, x + 1):  # 枚举最终有表演者的节目个数 j
            p = p * y % mod  # p 依次变成 y^1、y^2、…，即给 j 个节目各打一种分数
            ans = (ans + f[n][j] * p) % mod  # 把「分配方案数 × 打分方案数」累加进答案
        return ans  # 返回总方案数对 1e9+7 取余的结果
