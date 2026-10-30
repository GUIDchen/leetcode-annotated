# 题目：1232. 缀点成线（Check If It Is a Straight Line）
# 思路：取前两个点定出一条直线，其余点用叉积判断是否共线，叉积为 0 即斜率相同。
# 时间复杂度：O(n)，每个点检查一次；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def checkStraightLine(self, coordinates: List[List[int]]) -> bool:  # coordinates 是所有点的坐标，返回是否全部共线
        x1, y1 = coordinates[0]  # 解包得到第 1 个点，作为基准点
        x2, y2 = coordinates[1]  # 解包得到第 2 个点，用来确定直线方向
        for x, y in coordinates[2:]:  # 从第 3 个点开始逐个验证
            if (x - x1) * (y2 - y1) != (y - y1) * (x2 - x1):  # 叉积不为 0 表示该点不在前两点确定的直线上
                return False  # 发现不共线的点就直接返回
        return True  # 全部点共线
