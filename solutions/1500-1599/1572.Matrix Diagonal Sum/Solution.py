# 题目：1572. 矩阵对角线元素的和（Matrix Diagonal Sum）
# 思路：一次遍历每一行，把主对角线 row[i] 与副对角线 row[n-1-i] 相加；奇数阶时中心格子重合，用条件表达式补 0 避免重复。
# 时间复杂度：O(n)，n 为矩阵阶数，只遍历 n 行；空间复杂度：O(1)，只用常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def diagonalSum(self, mat: List[List[int]]) -> int:  # mat：n×n 的二维矩阵
        ans = 0  # 累加两条对角线元素之和
        n = len(mat)  # 矩阵的阶数
        for i, row in enumerate(mat):  # 逐行遍历，同时取得行下标 i 与该行 row
            j = n - i - 1  # 副对角线在这一行上的列下标
            ans += row[i] + (0 if j == i else row[j])  # 累加主对角线元素；重合（奇数阶中心）时补 0 防止重复
        return ans  # 返回两条对角线上元素的总和
