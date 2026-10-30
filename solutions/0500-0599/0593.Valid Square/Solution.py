# 题目：593. 有效的正方形（Valid Square）
# 思路：正方形四个点中任取三个，必有一个顶点与另外两点构成等腰直角三角形；只要四种三点组合都满足这个性质即为正方形。
# 时间复杂度：O(1)，只有四次常数级的三点检查；空间复杂度：O(1)，仅用常数个局部变量。
class Solution:  # LeetCode 约定的题解类
    def validSquare(  # 判断四个点能否构成正方形
        self, p1: List[int], p2: List[int], p3: List[int], p4: List[int]  # 四个点的坐标
    ) -> bool:  # 返回是否为正方形
        def check(a, b, c):  # 判断 a、b、c 三点能否构成等腰直角三角形
            (x1, y1), (x2, y2), (x3, y3) = a, b, c  # 一次性解包出三个点的坐标
            d1 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)  # a 到 b 的距离平方
            d2 = (x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3)  # a 到 c 的距离平方
            d3 = (x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3)  # b 到 c 的距离平方
            return any(  # 只要有一种「直角边配对」成立就算通过
                [  # 列表里是三种直角边配对各自的判定结果
                    d1 == d2 and d1 + d2 == d3 and d1,  # d1、d2 作直角边；末尾的 d1 用于排除重合点（非 0 即为真）
                    d2 == d3 and d2 + d3 == d1 and d2,  # d2、d3 作直角边，d1 作斜边
                    d1 == d3 and d1 + d3 == d2 and d1,  # d1、d3 作直角边，d2 作斜边
                ]  # 任意一项为真，any 就返回 True
            )

        return (  # 四种三点组合全部成立才是正方形（少检查一种可能把非正方形判成正方形）
            check(p1, p2, p3)  # 含 p1、p2、p3
            and check(p2, p3, p4)  # 含 p2、p3、p4
            and check(p1, p3, p4)  # 含 p1、p3、p4
            and check(p1, p2, p4)  # 含 p1、p2、p4
        )  # 四组结果做逻辑与，返回最终的布尔值
