# 题目：2087. 网格图中机器人回家的最小代价（Minimum Cost Homecoming of a Robot in a Grid）
# 思路：行方向与列方向的移动互相独立，绕路只会多花钱，因此分别累加起点到终点之间经过的每一行、每一列的代价，两者相加即最小总代价。
# 时间复杂度：O(m + n)，m、n 为需要跨越的行数与列数（两次切片求和）；空间复杂度：O(m + n)，切片只是临时对象。
class Solution:  # LeetCode 约定的题解类
    def minCost(  # startPos/homePos：起点与终点坐标；rowCosts/colCosts：每一行、每一列的移动代价
        self,  # self 是实例本身
        startPos: List[int],  # 起点坐标（行、列）
        homePos: List[int],  # 终点坐标（行、列）
        rowCosts: List[int],  # 每一行的移动代价
        colCosts: List[int],  # 每一列的移动代价
    ) -> int:  # 参数列表结束，返回最小总代价
        x0, y0 = startPos  # 解包起点坐标：x0 为行号，y0 为列号
        x1, y1 = homePos  # 解包终点坐标：x1 为行号，y1 为列号
        dx = sum(rowCosts[x0 + 1 : x1 + 1]) if x0 < x1 else sum(rowCosts[x1:x0])  # 行方向代价：向下走累加 rowCosts[x0+1:x1+1]，向上走累加 rowCosts[x1:x0]
        dy = sum(colCosts[y0 + 1 : y1 + 1]) if y0 < y1 else sum(colCosts[y1:y0])  # 列方向代价：向右累加 colCosts[y0+1:y1+1]，向左累加 colCosts[y1:y0]
        return dx + dy  # 行代价加列代价即最小总代价
