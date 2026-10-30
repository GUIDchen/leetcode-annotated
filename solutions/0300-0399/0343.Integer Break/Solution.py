# 题目：343. 整数拆分（Integer Break）
# 思路：动态规划，f[i] 表示 i 拆分后的最大乘积；枚举第一部分 j，在「继续拆 i-j」与「不拆 i-j」之间取较大者。
# 时间复杂度：O(n^2)，两层循环枚举拆分点；空间复杂度：O(n)，dp 数组。
class Solution:  # LeetCode 约定的题解类
    def integerBreak(self, n: int) -> int:  # n：要拆分的正整数（n >= 2）；返回拆分后各因子乘积的最大值
        f = [1] * (n + 1)  # 全部初始化为 1，等价于先把边界 f[1] 与 f[0] 置 1，避免下标越界
        for i in range(2, n + 1):  # 自小到大依次计算 f[2] 到 f[n]
            for j in range(1, i):  # 枚举第一部分 j，把 i 拆成 j 与 i-j
                f[i] = max(f[i], f[i - j] * j, (i - j) * j)  # 三者取最大：已有的 f[i]、继续拆 i-j 的 f[i-j]*j、不拆 i-j 的 (i-j)*j
        return f[n]  # 返回整数 n 拆分后的最大乘积
