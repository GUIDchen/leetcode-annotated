# 题目：62. 不同路径（Unique Paths）
# 思路：二维 DP，f[i][j] 表示到达 (i,j) 的路径数，递推式为「上方方案数 + 左方方案数」，起点置 1。
# 时间复杂度：O(m*n)，每格算一次；空间复杂度：O(m*n)，DP 表格。
class Solution:  # LeetCode 约定的题解类
    def uniquePaths(self, m: int, n: int) -> int:  # m 行 n 列，返回从左上到右下的路径总数
        f = [[0] * n for _ in range(m)]  # DP 表，全部初始化为 0
        f[0][0] = 1  # 起点方案数为 1，作为递推的基准
        for i in range(m):  # 从上到下逐行处理
            for j in range(n):  # 每行内从左到右，保证依赖项已就绪
                if i:  # i 为 0 时没有上方格子可转移
                    f[i][j] += f[i - 1][j]  # 从上方下来，累加上方的方案数
                if j:  # j 为 0 时没有左方格子可转移
                    f[i][j] += f[i][j - 1]  # 从左方过来，累加左方的方案数
        return f[-1][-1]  # 右下角的方案数即答案
