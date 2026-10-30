# 题目：1274. 矩形内船只的数目（Number of Ships in a Rectangle）
# 思路：在矩形上分治，先用 hasShips 判断当前矩形有没有船；有船且已缩成单点就计 1，否则四等分后递归求和。
# 时间复杂度：O(log(maxX·maxY)) 量级的 hasShips 调用；空间复杂度：O(log(maxX·maxY))，递归栈深度。
# """
# This is Sea's API interface.
# You should not implement it, or speculate about its implementation
# """
# class Sea:
#    def hasShips(self, topRight: 'Point', bottomLeft: 'Point') -> bool:
#
# class Point:
# 	def __init__(self, x: int, y: int):
# 		self.x = x
# 		self.y = y


class Solution:  # LeetCode 约定的题解类
    def countShips(self, sea: "Sea", topRight: "Point", bottomLeft: "Point") -> int:  # sea 只提供 hasShips 接口；topRight / bottomLeft 是当前矩形的右上、左下角
        def dfs(topRight, bottomLeft):  # dfs(topRight, bottomLeft)：统计该矩形内的船只数目
            x1, y1 = bottomLeft.x, bottomLeft.y  # 取出矩形左边界与下边界
            x2, y2 = topRight.x, topRight.y  # 取出矩形右边界与上边界
            if x1 > x2 or y1 > y2:  # 矩形范围非法
                return 0  # 非法矩形里不可能有船
            if not sea.hasShips(topRight, bottomLeft):  # 先问接口这个矩形里有没有船，没有就剪枝
                return 0  # 空矩形直接排除，不再细分
            if x1 == x2 and y1 == y2:  # 矩形已缩成一个点，且确认有船
                return 1  # 这个点就是一艘船
            midx = (x1 + x2) >> 1  # x 方向取中点，右移一位等价于整除 2
            midy = (y1 + y2) >> 1  # y 方向取中点
            a = dfs(topRight, Point(midx + 1, midy + 1))  # 右上象限递归
            b = dfs(Point(midx, y2), Point(x1, midy + 1))  # 左上象限递归
            c = dfs(Point(midx, midy), bottomLeft)  # 左下象限递归
            d = dfs(Point(x2, midy), Point(midx + 1, y1))  # 右下象限递归
            return a + b + c + d  # 四块互不重叠，求和就是船只总数

        return dfs(topRight, bottomLeft)  # 从题目给出的整块矩形开始分治
