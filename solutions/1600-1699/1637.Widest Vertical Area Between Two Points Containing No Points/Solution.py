# 题目：1637. 两点之间不包含任何点的最宽垂直区域（Widest Vertical Area Between Two Points Containing No Points）
# 思路：纵坐标不参与计算，把点按横坐标排序后，相邻两点横坐标差的最大值就是答案。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1) 额外空间（原地排序）。
class Solution:  # LeetCode 约定的题解类
    def maxWidthOfVerticalArea(self, points: List[List[int]]) -> int:  # points 是若干点坐标，返回最宽的、内部不含任何点的垂直区域宽度
        points.sort()  # 原地按横坐标排序（列表比较按元素逐项比较，x 相同时再看 y）
        return max(b[0] - a[0] for a, b in pairwise(points))  # pairwise 依次给出相邻两点，取横坐标差的最大值作为答案
