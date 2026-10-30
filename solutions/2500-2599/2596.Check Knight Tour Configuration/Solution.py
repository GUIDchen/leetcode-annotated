# 题目：2596. 检查骑士巡视方案（Check Knight Tour Configuration）
# 思路：用编号做下标反查每一步的坐标，再用 pairwise 依次检查相邻两步的坐标差是否为「日」字（1×2 或 2×1）。
# 时间复杂度：O(n²)，建表与校验各扫一遍 n×n；空间复杂度：O(n²)，坐标表存 n² 个坐标元组。
class Solution:  # LeetCode 约定的题解类
    def checkValidGrid(self, grid: List[List[int]]) -> bool:  # grid 是 n×n 的巡视编号矩阵；返回它是否描述一条合法的骑士巡视路线
        if grid[0][0]:  # 起点 (0,0) 的编号必须是 0：真值判断等价于 grid[0][0] != 0
            return False  # 起点不是 0，方案非法
        n = len(grid)  # 棋盘边长 n，总步数为 n * n
        pos = [None] * (n * n)  # pos[v] 保存编号 v 所在格子的坐标，先全部占位为 None
        for i in range(n):  # 枚举每一行
            for j in range(n):  # 枚举当前行的每一列
                pos[grid[i][j]] = (i, j)  # 反查：把格子 (i, j) 挂到它对应的步数编号下
        for (x1, y1), (x2, y2) in pairwise(pos):  # pairwise 依次取出相邻两步的坐标（Python 3.10+ 的 itertools.pairwise）
            dx, dy = abs(x1 - x2), abs(y1 - y2)  # 同时得到行差与列差的绝对值
            ok = (dx == 1 and dy == 2) or (dx == 2 and dy == 1)  # 骑士只能走「日」字：1×2 或 2×1
            if not ok:  # 这对相邻步不符合骑士规则
                return False  # 直接判定方案无效
        return True  # 所有相邻步都合法，返回 True
