# 题目：812. 最大三角形面积（Largest Triangle Area）
# 思路：三重循环枚举所有三点组合，用叉积绝对值的一半算面积并取最大。
# 时间复杂度：O(n^3)，n 为点数；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def largestTriangleArea(self, points: List[List[int]]) -> float:  # points 为点集，返回最大三角形面积
        ans = 0  # 当前最大面积
        for x1, y1 in points:  # 枚举第一个点
            for x2, y2 in points:  # 枚举第二个点
                for x3, y3 in points:  # 枚举第三个点
                    u1, v1 = x2 - x1, y2 - y1  # 以第一个点为起点的向量分量
                    u2, v2 = x3 - x1, y3 - y1  # 以第一个点为起点的另一个向量分量
                    t = abs(u1 * v2 - u2 * v1) / 2  # 叉积绝对值的一半即三角形面积
                    ans = max(ans, t)  # 更新最大值
        return ans  # 返回最大面积
