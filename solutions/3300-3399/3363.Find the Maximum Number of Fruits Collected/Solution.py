# 题目：3363. 最多可收集的水果数目（Find the Maximum Number of Fruits Collected）
# 思路：第一个孩子只能沿主对角线走到终点，路径固定；另两个孩子分别只在上三角（列 > 行）与下三角（行 > 列）活动，各自做一次网格 DP 求最大收集量，最后加上主对角线的水果。
# 时间复杂度：O(n^2)，两次 DP 各遍历半个网格；空间复杂度：O(n^2)，状态表 f。
class Solution:  # LeetCode 约定的题解类
    def maxCollectedFruits(self, fruits: List[List[int]]) -> int:  # fruits：n×n 的水果数目矩阵
        n = len(fruits)  # 网格边长
        f = [[-inf] * n for _ in range(n)]  # f[i][j]：走到 (i, j) 的最大收集数，-inf 表示不可达（源文件直接用 inf，未显式 import）
        f[0][n - 1] = fruits[0][n - 1]  # 右上角孩子的起点，先收集该格水果
        for i in range(1, n):  # 逐行向下推进
            for j in range(i + 1, n):  # 只在上三角（j > i）活动，避免与主对角线及另一个孩子的路径重叠
                f[i][j] = max(f[i - 1][j], f[i - 1][j - 1]) + fruits[i][j]  # 从上方的同列或左上格转移过来，再收集当前格
                if j + 1 < n:  # 右上方格子仍在界内时才能从那里转移
                    f[i][j] = max(f[i][j], f[i - 1][j + 1] + fruits[i][j])  # 尝试从右上方转移，与已有值取更优者
        f[n - 1][0] = fruits[n - 1][0]  # 左下角孩子的起点，先收集该格水果
        for j in range(1, n):  # 逐列向右推进
            for i in range(j + 1, n):  # 只在下三角（i > j）活动，与另一个孩子的区域不重叠
                f[i][j] = max(f[i][j - 1], f[i - 1][j - 1]) + fruits[i][j]  # 从左方的同行或左上格转移过来，再收集当前格
                if i + 1 < n:  # 左下方格子仍在界内时才能从那里转移
                    f[i][j] = max(f[i][j], f[i + 1][j - 1] + fruits[i][j])  # 尝试从左下方转移，与已有值取更优者
        return sum(fruits[i][i] for i in range(n)) + f[n - 2][n - 1] + f[n - 1][n - 2]  # 主对角线固定路径 + 两个孩子在终点前一格的最优值（终点那格已在对角线中计入）
