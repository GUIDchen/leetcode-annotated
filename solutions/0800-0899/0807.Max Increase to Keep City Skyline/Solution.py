# 题目：807. 保持城市天际线（Max Increase to Keep City Skyline）
# 思路：先求每行、每列的最大值作为两个方向的天际线，每个格子的上限就是两者较小值，用生成器表达式累加全部差值。
# 时间复杂度：O(mn)；空间复杂度：O(m + n)，只存行、列最大值。
class Solution:  # LeetCode 约定的题解类
    def maxIncreaseKeepingSkyline(self, grid: List[List[int]]) -> int:  # grid：建筑高度矩阵；返回所有建筑可以增加的总高度
        row_max = [max(row) for row in grid]  # 每行最大值，即左右方向看到的天际线
        col_max = [max(col) for col in zip(*grid)]  # zip(*grid) 转置后求每列最大值，即前后方向看到的天际线
        return sum(  # 对所有格子的可增高量求和
            min(row_max[i], col_max[j]) - x  # 上限是两个天际线的较小值，减去原高度就是增量
            for i, row in enumerate(grid)  # 遍历每一行
            for j, x in enumerate(row)  # 遍历行内每个格子
        )  # 生成器表达式结束
