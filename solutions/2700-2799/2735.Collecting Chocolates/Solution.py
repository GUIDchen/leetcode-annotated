# 题目：2735. 收集巧克力（Collecting Chocolates）
# 思路：f[i][j] 表示最多右移 j 次时位置 i 出现过的最低价；枚举总右移次数 j，把各位置的最低价求和再加上操作费 x*j，取所有 j 的最小值。
# 时间复杂度：O(n^2)，建表与枚举都是两重循环；空间复杂度：O(n^2)，需要 n×n 的 f 表。
class Solution:  # LeetCode 约定的题解类
    def minCost(self, nums: List[int], x: int) -> int:  # nums 是各位置初始价格，x 是整体右移一次的费用
        n = len(nums)  # 记录种类数 n
        f = [[0] * n for _ in range(n)]  # 预分配 n×n 的表，f[i][j] 后续会被逐个填充
        for i, v in enumerate(nums):  # enumerate 同时拿到位置 i 和初始价格 v
            f[i][0] = v  # 不右移时位置 i 的最低价就是它自己的初始价格
            for j in range(1, n):  # 枚举允许的右移次数 j = 1..n-1（右移 n 次回到原状）
                f[i][j] = min(f[i][j - 1], nums[(i - j) % n])  # 右移 j 次后位置 i 见到的是 nums[(i - j) % n]，与历史最小值取小（Python 取模天然为正）
        return min(sum(f[i][j] for i in range(n)) + x * j for j in range(n))  # 对每个右移次数 j：把各位置最低价求和再加上 x*j，最后在所有方案中取最小值
