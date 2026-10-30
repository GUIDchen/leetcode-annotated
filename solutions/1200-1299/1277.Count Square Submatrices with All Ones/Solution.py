# 题目：1277. 统计全为 1 的正方形子矩阵（Count Square Submatrices with All Ones）
# 思路：动态规划，f[i][j] 表示以 (i, j) 为右下角的全 1 正方形个数，等于左、上、左上三个方向的最小值加一。
# 时间复杂度：O(mn)，每个格子只计算一次；空间复杂度：O(mn)，额外开一张与原矩阵等大的 DP 表。
class Solution:  # LeetCode 约定的题解类
    def countSquares(self, matrix: List[List[int]]) -> int:  # matrix 是 0/1 矩阵，返回全 1 正方形子矩阵的总数
        m, n = len(matrix), len(matrix[0])  # m 为行数，n 为列数
        f = [[0] * n for _ in range(m)]  # f[i][j]：以 (i, j) 为右下角的全 1 正方形个数，初值 0
        ans = 0  # 累加所有位置的正方形个数，作为最终答案
        for i, row in enumerate(matrix):  # 逐行遍历，i 是行下标，row 是当前行
            for j, v in enumerate(row):  # 逐列遍历，j 是列下标，v 是当前格子的值
                if v == 0:  # 当前格子为 0，不可能充当全 1 正方形的右下角
                    continue  # 直接跳过，f[i][j] 保持 0
                if i == 0 or j == 0:  # 第一行或第一列只能容纳边长为 1 的正方形
                    f[i][j] = 1  # 所以这样的位置最多只有 1 个正方形
                else:  # 一般位置：左、上、左上三个方向的最小值决定能扩展出的边长
                    f[i][j] = min(f[i - 1][j - 1], f[i - 1][j], f[i][j - 1]) + 1  # 三个方向取短板再加当前格自身
                ans += f[i][j]  # 把以 (i, j) 为右下角的正方形数量累加进答案
        return ans  # 返回全 1 正方形子矩阵的总数
