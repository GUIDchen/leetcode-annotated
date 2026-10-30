# 题目：1401. 圆和矩形是否有重叠（Circle and Rectangle Overlapping）
# 思路：圆心到矩形的最近点按 x、y 两轴分别求：轴坐标落在矩形区间内则距离为 0，否则取到较近端点的差值；最后比较平方和与半径平方。
# 时间复杂度：O(1)，常数次算术；空间复杂度：O(1)，仅少量临时变量。
class Solution:  # LeetCode 约定的题解类
    def checkOverlap(  # 参数按行展开：圆心、半径、矩形对角点
        self,  # 实例本身
        radius: int,  # 圆半径
        xCenter: int,  # 圆心横坐标
        yCenter: int,  # 圆心纵坐标
        x1: int,  # 矩形左下角横坐标
        y1: int,  # 矩形左下角纵坐标
        x2: int,  # 矩形右上角横坐标
        y2: int,  # 矩形右上角纵坐标
    ) -> bool:  # 返回圆与矩形是否相交或包含
        def f(i: int, j: int, k: int) -> int:  # 求一维坐标 k 到闭区间 [i, j] 的最近距离
            if i <= k <= j:  # k 落在区间内部时链式比较为真
                return 0  # 在区间内，最近距离为 0
            return i - k if k < i else k - j  # k 在左端外取 i - k，在右端外取 k - j
        # 分轴计算圆心到矩形的最近距离

        a = f(x1, x2, xCenter)  # 横轴方向的最近距离
        b = f(y1, y2, yCenter)  # 纵轴方向的最近距离
        return a * a + b * b <= radius * radius  # 距离平方不超过半径平方即有重叠
