# 题目：3111. 覆盖所有点的最少矩形数目（Minimum Rectangles to Cover Points）
# 思路：贪心：按 x 升序排序，用一个变量记录当前矩形的右边界，遇到第一个越界的点就新开矩形并右移边界。
# 时间复杂度：O(n log n)，主要耗时在排序；空间复杂度：O(1)，只用了常数个额外变量（排序在原地进行）。
class Solution:  # LeetCode 约定的题解类
    def minRectanglesToCoverPoints(self, points: List[List[int]], w: int) -> int:  # points 是点集，w 是每个矩形宽度的上限
        points.sort()  # 按 x 升序排序，使矩形可以向右贪心地延伸覆盖
        ans, x1 = 0, -1  # ans 记矩形个数，x1 记当前矩形的右边界（-1 表示还没开矩形）
        for x, _ in points:  # 依次取出每个点的 x 坐标，忽略无用的 y 坐标
            if x > x1:  # 当前点超出了已有矩形的覆盖范围
                ans += 1  # 必须新开一个矩形
                x1 = x + w  # 新矩形右边界设为 x + w，可覆盖宽度 w 内的后续点
        return ans  # 返回覆盖所有点所需的最少矩形数
