# 题目：3033. 修改矩阵（Modify the Matrix）
# 思路：按列求出最大值，再把该列里的每个 -1 换成本列最大值；其余元素保持不动。
# 时间复杂度：O(m * n)，每列求最大值和替换各扫一遍；空间复杂度：O(1)，原地修改矩阵。
class Solution:  # LeetCode 约定的题解类
    def modifiedMatrix(self, matrix: List[List[int]]) -> List[List[int]]:  # matrix：待修改的矩阵，-1 是占位符
        m, n = len(matrix), len(matrix[0])  # m：行数；n：列数
        for j in range(n):  # 逐列处理，替换值由同列最大值决定
            mx = max(matrix[i][j] for i in range(m))  # 生成器表达式求这一列的最大值
            for i in range(m):  # 遍历该列的每一行
                if matrix[i][j] == -1:  # 只替换 -1 的位置
                    matrix[i][j] = mx  # 写成本列最大值
        return matrix  # 返回原地修改后的矩阵
