# 题目：240. 搜索二维矩阵 II（Search a 2D Matrix II）
# 思路：矩阵每行递增，于是逐行对目标值做二分查找；命中下标后还要判越界并确认值恰好相等。
# 时间复杂度：O(m log n)，m 行每行二分一次；空间复杂度：O(1)，只用常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:  # matrix 每行每列都递增，返回 target 是否存在
        for row in matrix:  # 逐行处理
            j = bisect_left(row, target)  # 在本行二分找第一个大于等于 target 的下标
            if j < len(matrix[0]) and row[j] == target:  # 先防止下标越界，再确认该位置的值恰好相等
                return True  # 命中目标值，立即返回
        return False  # 所有行都没命中
