# 题目：1453. 圆形靶内的最大飞镖数量（Maximum Number of Darts Inside of a Circular Dartboard）
# 核心思路：最优圆一定可以调整到边界经过两枚飞镖，枚举所有点对，求出半径为 r 且过这两点的两个圆心，分别统计覆盖数并取最大。
# 时间复杂度：O(n^3)，点对 O(n^2) 乘以每次统计 O(n)；空间复杂度：O(1) 额外空间（不含输入）。
class Solution:  # LeetCode 约定的题解类
    def numPoints(self, darts: list[list[int]], r: int) -> int:  # 返回半径为 r 的圆最多能覆盖的飞镖数量
        def countDarts(x, y):  # 内部函数：统计以 (x, y) 为圆心、半径为 r 的圆内的飞镖数量
            count = 0  # 计数器初始化
            for x1, y1 in darts:  # 遍历每一枚飞镖
                if dist((x, y), (x1, y1)) <= r + 1e-7:  # 欧氏距离不超过半径（加 1e-7 容差抵消浮点误差）
                    count += 1  # 该飞镖落在圆内，计数加一
            return count  # 返回圆内飞镖数量

        def possibleCenters(x1, y1, x2, y2):  # 内部函数：求同时经过两点、半径为 r 的圆心
            dx, dy = x2 - x1, y2 - y1  # 两点之间的位移向量
            d = sqrt(dx * dx + dy * dy)  # 两点间的距离，也就是圆上弦的长度
            if d > 2 * r:  # 弦长大于直径，不存在同时经过这两点的圆
                return []  # 直接返回空列表
            mid_x, mid_y = (x1 + x2) / 2, (y1 + y2) / 2  # 弦的中点，两个圆心都在过中点且垂直于弦的中垂线上
            dist_to_center = sqrt(r * r - (d / 2) * (d / 2))  # 由勾股定理求中点沿中垂线到圆心的距离
            offset_x = dist_to_center * dy / d  # 弦的单位法向量是 (dy/d, -dx/d)，乘以偏移距离得到 x 方向偏移
            offset_y = dist_to_center * -dx / d  # 同一法向量乘以偏移距离得到 y 方向偏移
            return [  # 返回两个候选圆心组成的列表
                (mid_x + offset_x, mid_y + offset_y),  # 中垂线一侧的圆心
                (mid_x - offset_x, mid_y - offset_y),  # 中垂线另一侧的圆心
            ]  # 列表结束，两个候选圆心都有可能是最优圆心

        n = len(darts)  # 飞镖总数
        max_darts = 1  # 至少能覆盖 1 枚飞镖（题目保证 n ≥ 1）

        for i in range(n):  # 枚举圆边界上的一枚飞镖
            for j in range(i + 1, n):  # 枚举圆边界上的另一枚飞镖（只取 j > i 避免重复）
                centers = possibleCenters(  # 求这两个点对应的候选圆心（参数跨行书写）
                    darts[i][0], darts[i][1], darts[j][0], darts[j][1]  # 两个点的坐标，作为 possibleCenters 的实参
                )  # 调用参数到此结束
                for center in centers:  # 逐个候选圆心统计覆盖的飞镖数
                    max_darts = max(max_darts, countDarts(center[0], center[1]))  # 用当前圆心的覆盖数刷新最大值

        return max_darts  # 返回最大覆盖数量
