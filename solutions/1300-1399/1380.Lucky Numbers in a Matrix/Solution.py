# 题目：1380. 矩阵中的幸运数（Lucky Numbers in a Matrix）
# 思路：行最小值集合与列最大值集合求交集，交集中的数既是所在行最小、又是所在列最大。
# 时间复杂度：O(m*n)，转置与求最值各扫描一遍矩阵；空间复杂度：O(m+n)，两个集合加起来最多 m+n 个元素。
class Solution:  # LeetCode 约定的题解类
    def luckyNumbers(self, matrix: List[List[int]]) -> List[int]:  # matrix：二维整数矩阵
        rows = {min(row) for row in matrix}  # 集合推导式：收集每一行的最小值（自动去重）
        cols = {max(col) for col in zip(*matrix)}  # zip(*matrix) 把矩阵转置，再逐列取最大值
        return list(rows & cols)  # 两个集合取交集，即既是行最小又是列最大的数，转成列表返回
