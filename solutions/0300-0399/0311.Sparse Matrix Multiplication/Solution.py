# 题目：311. 稀疏矩阵的乘法（Sparse Matrix Multiplication）
# 思路：按矩阵乘法定义三重循环直接累加，0 元素乘积为 0 不影响结果，因此不需要额外利用稀疏性。
# 时间复杂度：O(m·n·k)，m、n 为结果行列数，k 为公共维；空间复杂度：O(m·n)，只额外占用结果矩阵。
class Solution:  # LeetCode 约定的题解类
    def multiply(self, mat1: List[List[int]], mat2: List[List[int]]) -> List[List[int]]:  # mat1：m×k 矩阵；mat2：k×n 矩阵；返回 m×n 的乘积
        m, n = len(mat1), len(mat2[0])  # m：结果行数；n：结果列数（mat2 的列数）
        ans = [[0] * n for _ in range(m)]  # 结果矩阵，初始全 0，逐个位置累加
        for i in range(m):  # 枚举结果的每一行
            for j in range(n):  # 枚举结果的每一列
                for k in range(len(mat2)):  # 枚举公共维 k，即 mat2 的行数（等于 mat1 的列数）
                    ans[i][j] += mat1[i][k] * mat2[k][j]  # 累加「第 i 行第 k 列」与「第 k 行第 j 列」的乘积
        return ans  # 返回乘积矩阵
