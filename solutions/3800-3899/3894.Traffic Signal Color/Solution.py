# 题目：3894. 交通信号灯的颜色（Traffic Signal Color）
# 思路：直接按题目给定的区间判定：0 为绿灯，30 为橙灯，(30, 90] 为红灯，其余为非法输入。
# 时间复杂度：O(1)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def trafficSignal(self, timer: int) -> str:  # timer：交通灯的计时值
        if timer == 0:  # 计时为 0 表示绿灯
            return "Green"  # 返回 Green
        if timer == 30:  # 计时为 30 表示橙灯
            return "Orange"  # 返回 Orange
        if 30 < timer <= 90:  # 计时在 30 到 90 之间（不含 30）表示红灯
            return "Red"  # 返回 Red
        return "Invalid"  # 其余取值都是非法输入
