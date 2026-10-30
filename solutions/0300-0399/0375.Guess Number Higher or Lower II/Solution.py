# 题目：375. 猜数字大小 II（Guess Number Higher or Lower II）
# 思路：区间 DP，f[i][j] 表示在 [i, j] 中保证猜中所需的最少金额；枚举本轮猜的 k，取 k + max(两侧区间) 的最小值。
# 时间复杂度：O(n^3)，三层循环；空间复杂度：O(n^2)，二维 DP 表。
class Solution:  # LeetCode 约定的题解类
    def getMoneyAmount(self, n: int) -> int:  # n 为最大数字，返回保证猜中所需要的最少金额
        f = [[0] * (n + 1) for _ in range(n + 1)]  # f[i][j]：在区间 [i, j] 中保证猜中所需的最少金额，先全部置 0
        for i in range(n - 1, 0, -1):  # 左端点从大到小递推，保证依赖的更短区间已经算好
            for j in range(i + 1, n + 1):  # 右端点从 i + 1 起，区间长度至少为 2
                f[i][j] = j + f[i][j - 1]  # 最坏情况先按「每轮都猜右端点 j」估计一个上界
                for k in range(i, j):  # 枚举这一轮猜的数字 k，k = j 的情形已作为上界
                    f[i][j] = min(f[i][j], max(f[i][k - 1], f[k + 1][j]) + k)  # 猜 k 的花费 = k + 两侧区间中更坏的一侧，对所有 k 取最小
        return f[1][n]  # 答案就是整个区间 [1, n] 上的最少金额
