# 题目：1692. 计算分配糖果的不同方式（Count Ways to Distribute Candies）
# 思路：第二类斯特林数；f[i][j] 表示前 i 颗糖恰放进 j 个非空袋子的方案数，转移 f[i][j] = f[i-1][j]*j + f[i-1][j-1]。
# 时间复杂度：O(n * k)，双重循环填表；空间复杂度：O(n * k)，保存整张二维 dp 表。
class Solution:  # LeetCode 约定的题解类
    def waysToDistribute(self, n: int, k: int) -> int:  # n：糖果总数；k：恰好分成的非空袋子数
        mod = 10**9 + 7  # 取模常量，防止方案数过大
        f = [[0] * (k + 1) for _ in range(n + 1)]  # f[i][j]：前 i 颗糖放进 j 个非空袋子的方案数
        f[0][0] = 1  # 边界：0 颗糖、0 个袋子只有一种空方案，作为递推起点
        for i in range(1, n + 1):  # 逐颗放入糖果，从第 1 颗到第 n 颗
            for j in range(1, k + 1):  # 枚举当前已用到的非空袋子数
                f[i][j] = (f[i - 1][j] * j + f[i - 1][j - 1]) % mod  # 放进已有 j 个袋子之一，或单独新开一个袋子
        return f[n][k]  # 答案：n 颗糖恰好分成 k 个非空袋子的方案数
