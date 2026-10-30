# 题目：223. 矩形面积（Rectangle Area）
# 思路：总面积 = A 面积 + B 面积 - 交集面积；交集宽 = min(右边界) - max(左边界)，高同理，负值截断为 0。
# 时间复杂度：O(1)，只做常数次算术运算；空间复杂度：O(1)，只用了几个局部变量。
class Solution:  # LeetCode 约定的题解类
    def computeArea(  # 两个矩形分别给出左下角与右上角，返回它们覆盖的总面积
        self,
        ax1: int,  # A 矩形左下角的 x 坐标
        ay1: int,  # A 矩形左下角的 y 坐标
        ax2: int,  # A 矩形右上角的 x 坐标
        ay2: int,  # A 矩形右上角的 y 坐标
        bx1: int,  # B 矩形左下角的 x 坐标
        by1: int,  # B 矩形左下角的 y 坐标
        bx2: int,  # B 矩形右上角的 x 坐标
        by2: int,  # B 矩形右上角的 y 坐标
    ) -> int:  # 返回值是两矩形覆盖的总面积，重叠部分只算一次
        a = (ax2 - ax1) * (ay2 - ay1)  # A 的面积 = 宽 × 高
        b = (bx2 - bx1) * (by2 - by1)  # B 的面积 = 宽 × 高
        width = min(ax2, bx2) - max(ax1, bx1)  # 交集宽：右边界取小、左边界取大再相减，不相交时为负
        height = min(ay2, by2) - max(ay1, by1)  # 交集高：同理取 y 方向的公共部分
        return a + b - max(height, 0) * max(width, 0)  # 总面积 = A + B - 交集；max(..., 0) 把不相交时的负值截断为 0
