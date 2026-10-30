# 题目：149. 直线上最多的点数（Max Points on a Line）
# 思路：枚举两个点确定一条直线，再用叉积判断其余点是否共线；叉积两式相等说明三点共线。
# 时间复杂度：O(n^3)，三重循环枚举点对与第三点；空间复杂度：O(1)，只用常数个变量。
class Solution:  # 题目要求的题解类
    def maxPoints(self, points: List[List[int]]) -> int:  # points 是二维坐标点集，返回落在同一直线上的最多点数
        n = len(points)  # 点的总个数
        ans = 1  # 至少有一个点时，答案至少为 1
        for i in range(n):  # 枚举直线上的第一个点
            x1, y1 = points[i]  # 取出第 i 个点的坐标
            for j in range(i + 1, n):  # 枚举第二个点：两个不同点唯一确定一条直线
                x2, y2 = points[j]  # 取出第 j 个点的坐标
                cnt = 2  # 这条直线目前至少包含 i、j 这两个点
                for k in range(j + 1, n):  # 再枚举其后的点，检查它们是否也在这条直线上
                    x3, y3 = points[k]  # 取出第 k 个点的坐标
                    a = (y2 - y1) * (x3 - x1)  # 叉积的第一项 (y2-y1)*(x3-x1)
                    b = (y3 - y1) * (x2 - x1)  # 叉积的第二项 (y3-y1)*(x2-x1)，两项相等即三点共线
                    cnt += a == b  # 共线则计数加一（True 当作 1）
                ans = max(ans, cnt)  # 用这条直线上的点数更新答案
        return ans  # 返回最多的共线点数
