# 题目：3239. 最少翻转次数使二进制矩阵回文 I（Minimum Number of Flips to Make Binary Grid Palindromic I）
# 思路：行回文与列回文满足其一即可，于是分别统计两种方案的花费并取最小值；每组不对称格子翻一次就够。
# 时间复杂度：O(m × n)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def minFlips(self, grid: List[List[int]]) -> int:  # grid 是 0/1 矩阵，返回最少翻转次数
        m, n = len(grid), len(grid[0])  # m 行数，n 列数
        cnt1 = cnt2 = 0  # cnt1 记行回文的代价，cnt2 记列回文的代价
        for row in grid:  # 逐行检查左右对称位置
            for j in range(n // 2):  # 只看前一半列，与对称列 n-j-1 配对
                if row[j] != row[n - j - 1]:  # 两个对称元素不同就必须翻一个
                    cnt1 += 1  # 累加行回文代价
        for j in range(n):  # 逐列检查上下对称位置
            for i in range(m // 2):  # 只看前一半行，与对称行 m-i-1 配对
                if grid[i][j] != grid[m - i - 1][j]:  # 两个对称元素不同就必须翻一个
                    cnt2 += 1  # 累加列回文代价
        return min(cnt1, cnt2)  # 两种方案取较小者
