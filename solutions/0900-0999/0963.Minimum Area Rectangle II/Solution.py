# 题目：963. 最小面积矩形 II（Minimum Area Rectangle II）
# 思路：枚举直角顶点与两条邻边，用平行四边形公式求出第四个顶点，若它在点集中且两邻边垂直，就用两边长度乘积更新最小面积。
# 时间复杂度：O(n^3)，三重枚举顶点；空间复杂度：O(n)，集合保存全部点。
class Solution:  # LeetCode 约定的题解类
    def minAreaFreeRect(self, points: List[List[int]]) -> float:  # points 是平面上所有点，返回最小矩形面积（不存在则返回 0）
        s = {(x, y) for x, y in points}  # 集合：把所有点存起来，方便 O(1) 判断某个坐标是否存在
        n = len(points)  # 点的个数
        ans = inf  # ans 记录最小面积，先用 inf 表示「还没找到」
        for i in range(n):  # 枚举直角顶点 i
            x1, y1 = points[i]  # 直角顶点的坐标
            for j in range(n):  # 枚举与 i 相邻的第二个顶点 j
                if j != i:  # 跳过与 i 相同的点
                    x2, y2 = points[j]  # 第二个顶点的坐标
                    for k in range(j + 1, n):  # 枚举第三个顶点 k，从 j+1 开始减少重复
                        if k != i:  # 跳过与 i 相同的点
                            x3, y3 = points[k]  # 第三个顶点的坐标
                            x4 = x2 - x1 + x3  # 平行四边形法则：第四点横坐标 = 点 j + 点 k - 点 i
                            y4 = y2 - y1 + y3  # 第四点纵坐标
                            if 0 <= x4 <= 40000 and 0 <= y4 <= 40000 and (x4, y4) in s:  # 第四点在坐标范围内且确实存在时，才可能构成矩形
                                v21 = (x2 - x1, y2 - y1)  # 从 i 指向 j 的向量
                                v31 = (x3 - x1, y3 - y1)  # 从 i 指向 k 的向量
                                if v21[0] * v31[0] + v21[1] * v31[1] == 0:  # 点积为 0 说明两向量垂直，即夹角是直角
                                    w = sqrt(v21[0] ** 2 + v21[1] ** 2)  # 邻边 j 的长度
                                    h = sqrt(v31[0] ** 2 + v31[1] ** 2)  # 邻边 k 的长度
                                    ans = min(ans, w * h)  # 面积 = 两条邻边长度之积，取最小值
        return 0 if ans == inf else ans  # 若从未更新过 ans 说明不存在矩形，返回 0
