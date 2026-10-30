# 题目：2500. 删除每行中的最大值（Delete Greatest Value in Each Row）
# 思路：先把每行升序排序，再按列看：第 j 列就是第 j 轮各行的最大值，取列最大值累加即得答案。
# 时间复杂度：O(m·n log n)，每行排序 O(n log n)；空间复杂度：O(m·n)，zip 按列展开需要额外空间。
class Solution:  # LeetCode 约定的题解类
    def deleteGreatestValue(self, grid: List[List[int]]) -> int:  # grid：m 行 n 列的矩阵；返回每轮删除的最大值之和
        for row in grid:  # 逐行处理：把每行升序排序，最大值排到行尾
            row.sort()  # 原地排序，结果写回 grid，无需额外数组
        return sum(max(col) for col in zip(*grid))  # zip(*grid) 把矩阵按列转置，每轮取一列；max 得到该轮删除的最大值，sum 累加全部轮次
