# 题目：867. 转置矩阵（Transpose Matrix）
# 思路：转置即行列互换，用 zip(*matrix) 把原矩阵的每一列打包成新矩阵的一行。
# 时间复杂度：O(mn)，每个元素搬一次；空间复杂度：O(mn)，需要新矩阵存放结果。
class Solution:  # LeetCode 约定的题解类
    def transpose(self, matrix: List[List[int]]) -> List[List[int]]:  # matrix 是原矩阵，返回它的转置矩阵
        return [list(row) for row in zip(*matrix)]  # zip(*matrix) 把每一列打包成元组（等价于行列互换），list(row) 再把元组转成题目要求的列表
