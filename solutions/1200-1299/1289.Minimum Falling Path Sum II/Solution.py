# 题目：1289. 下降路径最小和 II（Minimum Falling Path Sum II）
# 核心思路：滚动数组 DP，f[j] 表示上一行落在第 j 列的最小路径和；本行每列累加「上一行不同列的最小值」，逐行递推。
# 时间复杂度：O(n^3)，每行要对 n 列各扫 n 列；空间复杂度：O(n)，只保留上一行与当前行两组状态。
class Solution:  # LeetCode 约定的题解类
    def minFallingPathSum(self, grid: List[List[int]]) -> int:  # 题解方法对外可见
        n = len(grid)  # grid 是 n×n 矩阵，返回下降路径最小和，且相邻两行不能选同一列
        f = [0] * n  # n 是矩阵的边长
        for row in grid:  # f[j] 表示处理到上一行、且落在第 j 列时的最小路径和，初始全 0
            g = row[:]  # inf 是一个足够大的数，用来表示「当前还没有合法前驱」
            for i in range(n):  # 逐行向下推进动态规划
                g[i] += min((f[j] for j in range(n) if j != i), default=0)  # g 拷贝当前行，作为本行的 DP 结果
            f = g  # 枚举本行选中的列 i
        return min(f)  # t 记录上一行中「列号不等于 i」的最小 f 值
