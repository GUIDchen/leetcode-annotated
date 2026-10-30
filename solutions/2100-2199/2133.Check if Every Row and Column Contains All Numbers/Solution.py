# 题目：2133. 检查是否每一行每一列都包含全部整数（Check if Every Row and Column Contains All Numbers）
# 思路：把矩阵的每一行和转置后的每一行拼在一起，逐条检查去重后的长度是否等于 n；长度等于 n 说明恰好是 1..n。
# 时间复杂度：O(n^2)，需要检查 n 行与 n 列的全部元素；空间复杂度：O(n)，每个集合最多存 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def checkValid(self, matrix: List[List[int]]) -> bool:  # matrix：n × n 的待检查矩阵
        n = len(matrix)  # 矩阵的阶数 n，也是每行每列应有的元素个数
        return all(len(set(row)) == n for row in chain(matrix, zip(*matrix)))  # 逐行检查原矩阵与转置矩阵（即原矩阵的各列）
