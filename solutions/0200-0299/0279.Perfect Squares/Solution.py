# 题目：279. 完全平方数（Perfect Squares）
# 思路：完全背包 DP，物品是 1²,2²,...,m²，f[i][j] 表示前 i 个平方数凑出 j 的最少个数。
# 时间复杂度：O(m·n)=O(n√n)；空间复杂度：O(m·n)，二维 DP 表。
class Solution:  # LeetCode 约定的题解类
    def numSquares(self, n: int) -> int:  # n 是目标和，返回最少需要的完全平方数个数
        m = int(sqrt(n))  # 能用到的最大的平方根根号 n
        f = [[inf] * (n + 1) for _ in range(m + 1)]  # 二维 DP 表，先全部初始化为无穷大 inf
        f[0][0] = 0  # 一个数都不选就能凑出 0，代价为 0
        for i in range(1, m + 1):  # 逐个枚举可用的平方数 i²
            for j in range(n + 1):  # 枚举要凑出的和 j
                f[i][j] = f[i - 1][j]  # 不选 i²：继承前 i-1 个物品的答案
                if j >= i * i:  # 容量还放得下一个 i²
                    f[i][j] = min(f[i][j], f[i][j - i * i] + 1)  # 选 i²：同层转移，同一个平方数可重复使用
        return f[m][n]  # 用前 m 个平方数凑出 n 的最少个数
