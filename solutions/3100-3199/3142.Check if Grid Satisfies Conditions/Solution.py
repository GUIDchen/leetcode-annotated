# 题目：3142. 判断矩阵是否满足条件（Check if Grid Satisfies Conditions）
# 思路：逐格检查两条约束——与正下方格子必须不同，与正右方格子必须不相等（即同行相邻不能相同）。
# 时间复杂度：O(m*n)，每个格子只做常数次比较；空间复杂度：O(1)，只用了行列计数变量。
class Solution:  # LeetCode 约定的题解类
    def satisfiesConditions(self, grid: List[List[int]]) -> bool:  # grid 是待检查的矩阵，返回是否满足条件
        m, n = len(grid), len(grid[0])  # m 是行数，n 是列数
        for i, row in enumerate(grid):  # 逐行遍历，i 是行号
            for j, x in enumerate(row):  # 逐列遍历，x 是当前格子的值
                if i + 1 < m and x != grid[i + 1][j]:  # 要求同一列上下相邻的两个元素不同
                    return False  # 相同即违反条件
                if j + 1 < n and x == grid[i][j + 1]:  # 要求同一行左右相邻的两个元素相等
                    return False  # 相同即违反条件
        return True  # 所有格子都没被否决，说明满足条件
