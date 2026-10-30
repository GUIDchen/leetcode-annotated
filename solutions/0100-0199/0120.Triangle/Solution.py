# 题目：120. 三角形最小路径和（Triangle）
# 思路：自底向上 DP，f[i][j] 表示从 (i, j) 走到最底部的最小路径和，等于下方两个相邻位置的最小值再加当前格子的值。
# 时间复杂度：O(n^2)，每个格子算一次；空间复杂度：O(n^2)，需要 (n+1) x (n+1) 的 DP 表。
class Solution:  # LeetCode 约定的题解类
    def minimumTotal(self, triangle: List[List[int]]) -> int:  # triangle 是金字塔形二维列表，返回自顶向下的最小路径和
        n = len(triangle)  # 三角形的层数
        f = [[0] * (n + 1) for _ in range(n + 1)]  # DP 表多开一行一列，越界的下方位置天然是 0
        for i in range(n - 1, -1, -1):  # 从最底下一行开始往上递推
            for j in range(i + 1):  # 第 i 行有 i+1 个元素
                f[i][j] = min(f[i + 1][j], f[i + 1][j + 1]) + triangle[i][j]  # 取下方两个相邻位置的最小值，加上当前格子的值
        return f[0][0]  # 顶点处就是全局最小路径和
