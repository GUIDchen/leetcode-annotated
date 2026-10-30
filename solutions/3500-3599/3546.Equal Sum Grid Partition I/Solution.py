# 题目：3546. 等和矩阵分割 I（Equal Sum Grid Partition I）
# 思路：总和为奇数时必然无法平分；否则分别累加行前缀和与列前缀和，存在等于总和一半且两侧都非空的切割线即可。
# 时间复杂度：O(m * n)，行方向与列方向各遍历一次矩阵；空间复杂度：O(m * n)，zip(*grid) 会生成转置的中间结构。
class Solution:  # LeetCode 约定的题解类
    def canPartitionGrid(self, grid: List[List[int]]) -> bool:  # grid：m 行 n 列的整数矩阵
        s = sum(sum(row) for row in grid)  # 矩阵所有元素的总和
        if s % 2:  # 总和为奇数时无法分成两个相等的部分
            return False  # 直接判定不可能
        pre = 0  # 前缀和，先用来统计按行切分时的上方部分
        for i, row in enumerate(grid):  # 枚举行切割线：第一块包含第 0~i 行
            pre += sum(row)  # 把第 i 行的元素和加入前缀和
            if pre * 2 == s and i != len(grid) - 1:  # 上方和正好是总和一半，且下方还有行
                return True  # 找到合法的水平切割线
        pre = 0  # 重置前缀和，改为统计按列切分时的左侧部分
        for j, col in enumerate(zip(*grid)):  # 用 zip(*grid) 转置矩阵后逐列枚举列切割线
            pre += sum(col)  # 把第 j 列的元素和加入前缀和
            if pre * 2 == s and j != len(grid[0]) - 1:  # 左侧和正好是总和一半，且右侧还有列
                return True  # 找到合法的垂直切割线
        return False  # 所有切割线都不满足条件
