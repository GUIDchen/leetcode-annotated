# 题目：2849. 判断能否在给定时间到达单元格（Determine if a Cell Is Reachable at a Given Time）
# 核心思路：每步可横、竖或斜走一格，最少步数是横纵坐标差的较大者；只有起点等于终点且 t == 1 时需要特判。
# 时间复杂度：O(1)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def isReachableAtTime(self, sx: int, sy: int, fx: int, fy: int, t: int) -> bool:  # 起点 (sx, sy)、终点 (fx, fy) 与限定时间 t
        if sx == fx and sy == fy:  # 起终点重合，需要单独判断
            return t != 1  # 1 秒内既不能原地停 0 步也无法往返，故 t == 1 不可达；t 为 0 或大于 1 都可达
        dx = abs(sx - fx)  # 横向需要跨越的距离
        dy = abs(sy - fy)  # 纵向需要跨越的距离
        return max(dx, dy) <= t  # 允许斜走，最少步数为两差值较大者，不超过 t 即可达
