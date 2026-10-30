# 3394. 判断网格图能否被切割成块 / Check if Grid can be Cut into Sections
# 核心思路：把每个矩形拆成起始边与结束边两个事件点，按坐标排序后做扫描线，统计覆盖数归零的次数，某方向出现 3 次即可切出 3 块，x、y 任一方向满足即可
# 复杂度：时间 O(n log n)（排序主导）、空间 O(n)
class Solution:  # 定义 Solution 类
    def countLineIntersections(self, coordinates: List[tuple[int, int]]) -> bool:  # 扫描线统计该方向上可切出的段数是否达到 3
        lines = 0  # 已扫描到的可切线数量
        overlap = 0  # 当前被矩形覆盖的区间数（重叠计数）
        for value, marker in coordinates:  # 按坐标顺序遍历所有事件点
            if marker == 0:  # 若是结束事件（marker 为 0）
                overlap -= 1  # 覆盖数减一
            else:  # 否则是起始事件
                overlap += 1  # 覆盖数加一

            if overlap == 0:  # 覆盖数重新归零，说明此处可以切一刀
                lines += 1  # 可切线数加一

        return lines >= 3  # 可切线达到 3 条即能把网格切成 3 块

    def checkValidCuts(self, n: int, rectangles: List[List[int]]) -> bool:  # 判断能否沿水平或垂直方向把矩形切成 3 块
        y_coordinates = []  # y 方向的事件点列表
        x_coordinates = []  # x 方向的事件点列表

        for rect in rectangles:  # 枚举每个矩形，拆成起始事件与结束事件
            x1, y1, x2, y2 = rect  # 取出矩形的左下与右上角坐标
            y_coordinates.append((y1, 1))  # start  # 记录 y 方向下边界，标记为起始（1）
            y_coordinates.append((y2, 0))  # end  # 记录 y 方向上边界，标记为结束（0）

            x_coordinates.append((x1, 1))  # start  # 记录 x 方向左边界，标记为起始（1）
            x_coordinates.append((x2, 0))  # end  # 记录 x 方向右边界，标记为结束（0）

        # Sort by coordinate value, and for tie, put end (0) before start (1)
        y_coordinates.sort(key=lambda x: (x[0], x[1]))  # 按 (坐标, 类型) 排序，同一坐标时结束边排在起始边之前
        x_coordinates.sort(key=lambda x: (x[0], x[1]))  # 同样对 x 方向排序

        return self.countLineIntersections(  # 先判断 y 方向能否切出 3 块
            y_coordinates  # 传入 y 方向的事件点列表
        ) or self.countLineIntersections(x_coordinates)  # 若 y 方向不满足，再看 x 方向能否切出 3 块
