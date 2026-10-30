# 题目：2304. 网格中的最小路径代价（Minimum Path Cost in a Grid）
# 思路：按行动态规划，f[k] 表示到达上一行第 k 列的最小总代价；本行每列 j 枚举全部来源列 k 做转移取最小，逐行滚动更新。
# 时间复杂度：O(m * n^2)，m 行每行 n^2 次转移；空间复杂度：O(n)，只用两行的滚动数组。
class Solution:  # LeetCode 约定的题解类
    def minPathCost(self, grid: List[List[int]], moveCost: List[List[int]]) -> int:  # grid：每格的代价；moveCost：由上一行某格的值移动到本行某列的额外代价
        m, n = len(grid), len(grid[0])  # m 是行数，n 是列数
        f = grid[0]  # 初始化：第一行只能从本格开始，代价就是格子本身的值
        for i in range(1, m):  # 从第二行开始逐行推进
            g = [inf] * n  # g 保存到达本行各列的最小代价，先全部置为无穷大 inf
            for j in range(n):  # 枚举本行要落入的列 j
                for k in range(n):  # 枚举上一行的来源列 k，尝试所有可能的前驱
                    g[j] = min(g[j], f[k] + moveCost[grid[i - 1][k]][j] + grid[i][j])  # 转移：上一行第 k 列的代价 + 从 grid[i-1][k] 这一格值移动到第 j 列的代价 + 本格代价，取最小值
            f = g  # 把本行结果换成 f，进入下一轮滚动
        return min(f)  # 最后一行任意一列都可以作为终点，取其中最小的代价
