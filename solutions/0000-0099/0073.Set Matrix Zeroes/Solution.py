# 题目：73. 矩阵置零（Set Matrix Zeroes）
# 思路：先记录哪些行、哪些列含有 0，再统一把这些行列交叉处的元素置 0；分两趟做可以避免「边改边查」把新置的 0 误当成原始 0。
# 时间复杂度：O(m·n)，矩阵完整扫描两遍；空间复杂度：O(m + n)，额外用两个布尔数组记录行与列的标记。
class Solution:  # LeetCode 约定的题解类
    def setZeroes(self, matrix: List[List[int]]) -> None:  # matrix：待处理的矩阵；要求原地修改，故返回 None
        m, n = len(matrix), len(matrix[0])  # m 为行数，n 为列数（题目保证矩阵非空）
        row = [False] * m  # row[i] 为 True 表示第 i 行出现过 0，整行要清零
        col = [False] * n  # col[j] 为 True 表示第 j 列出现过 0，整列要清零
        for i in range(m):  # 第一趟：遍历每一行
            for j in range(n):  # 遍历该行的每一列
                if matrix[i][j] == 0:  # 找到一个原始的 0
                    row[i] = col[j] = True  # 链式赋值：把它所在的行和列同时标记
        for i in range(m):  # 第二趟：按标记统一清零
            for j in range(n):  # 遍历该行的每一列
                if row[i] or col[j]:  # 只要所在行或所在列被标记过
                    matrix[i][j] = 0  # 就把这个位置置 0
