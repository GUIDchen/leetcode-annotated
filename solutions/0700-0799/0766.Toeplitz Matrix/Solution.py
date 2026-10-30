# 题目：766. 托普利茨矩阵（Toeplitz Matrix）
# 思路：同一斜线上的元素相等，等价于每个元素都等于它左上角的元素，逐格比较即可。
# 时间复杂度：O(mn)，遍历除首行首列外的所有元素；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def isToeplitzMatrix(self, matrix: List[List[int]]) -> bool:  # matrix：待判定的二维矩阵
        m, n = len(matrix), len(matrix[0])  # m 是行数，n 是列数
        for i in range(1, m):  # 从第二行开始比较（首行没有左上角元素）
            for j in range(1, n):  # 从第二列开始比较（首列没有左上角元素）
                if matrix[i][j] != matrix[i - 1][j - 1]:  # 与左上角邻居不相等则说明同一斜线不一致
                    return False  # 立刻判定不是托普利茨矩阵
        return True  # 全部检查通过，是托普利茨矩阵
