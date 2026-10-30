# 题目：48. 旋转图像（Rotate Image）
# 核心思路：顺时针旋转 90 度等于先沿水平中线上下翻转，再沿主对角线转置，两次原地交换即可，无需额外矩阵。
# 时间复杂度：O(n²)，要处理所有元素；空间复杂度：O(1)，原地交换。
class Solution:  # LeetCode 约定的题解类
    def rotate(self, matrix: List[List[int]]) -> None:  # matrix 是 n×n 方阵，要求原地顺时针旋转 90 度
        n = len(matrix)  # 方阵的边长
        for i in range(n >> 1):  # 只处理上半部分的行就够：n >> 1 即 n/2，中间行不用动
            for j in range(n):  # 逐列遍历这一整行
                matrix[i][j], matrix[n - i - 1][j] = matrix[n - i - 1][j], matrix[i][j]  # 第 i 行与上下对称的第 n-i-1 行对应元素交换，完成上下翻转
        for i in range(n):  # 接着沿主对角线做转置
            for j in range(i):  # 只遍历下三角（j < i），避免把已经交换过的元素又换回去
                matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]  # 交换 (i,j) 与 (j,i)，完成沿主对角线转置
