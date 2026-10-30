# 3899. 三角形的内角度数 / Angles of a Triangle
# 核心思路：排序后先用两边之和大于第三边判定合法性，再用余弦定理求出两个角，第三个角由三角形内角和 180 度相减得到。
# 复杂度：时间 O(1)，空间 O(1)。
class Solution:  # 题解类
    def internalAngles(self, sides: list[int]) -> list[float]:  # sides 为三边长，返回内角度数；无法构成三角形时返回空列表
        sides.sort()  # 排序后按 a <= b <= c 处理
        a, b, c = sides  # 解包出三条边
        if a + b <= c:  # 两边之和不大于第三边则不能构成三角形
            return []  # 返回空列表表示不合法
        A = degrees(acos((b**2 + c**2 - a**2) / (2 * b * c)))  # 余弦定理求角 A（弧度转角度）
        B = degrees(acos((a**2 + c**2 - b**2) / (2 * a * c)))  # 余弦定理求角 B（弧度转角度）
        C = 180 - A - B  # 内角和 180 度，相减得到角 C
        return [A, B, C]  # 返回三个内角
