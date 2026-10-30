# 题目：1266. 访问所有点的最小时间（Minimum Time Visiting All Points）
# 思路：相邻两点的最短耗时等于切比雪夫距离 max(|dx|, |dy|)，用 pairwise 取相邻点对后求距离并求和。
# 时间复杂度：O(n)，每个点对计算一次；空间复杂度：O(1)，生成器不额外存列表。
class Solution:  # LeetCode 约定的题解类
    def minTimeToVisitAllPoints(self, points: List[List[int]]) -> int:  # points 是按顺序访问的点列表，返回总耗时
        return sum(  # sum 对所有相邻点对的距离求和；生成器表达式惰性求值，不会额外建列表
            max(abs(p1[0] - p2[0]), abs(p1[1] - p2[1])) for p1, p2 in pairwise(points)  # pairwise 依次给出相邻两点 (p1, p2)，切比雪夫距离即两份坐标差的绝对值的较大者
        )  # 结束 sum 的参数列表
