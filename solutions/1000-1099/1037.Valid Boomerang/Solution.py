# 题目：1037. 有效的回旋镖（Valid Boomerang）
# 思路：用叉积判断三点是否共线，两段斜率交叉相乘后不相等即三点不共线，三点不共线才构成回旋镖。
# 时间复杂度：O(1)，只做常数次运算；空间复杂度：O(1)，只用了几个局部变量。
class Solution:  # LeetCode 约定的题解类
    def isBoomerang(self, points: List[List[int]]) -> bool:  # points 是三个点的坐标，返回它们是否构成回旋镖
        (x1, y1), (x2, y2), (x3, y3) = points  # 一次解包出三个点的横纵坐标
        return (y2 - y1) * (x3 - x2) != (y3 - y2) * (x2 - x1)  # 交叉相乘比较两段斜率，不相等说明三点不共线，返回 True
