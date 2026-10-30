# 题目：849. 到最近的人的最大距离（Maximize Distance to Closest Person）
# 思路：记录第一个和最后一个已坐人的位置，并统计相邻两人的最大间隔；答案取左端、右端、中间间隔一半三者最大值。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxDistToClosest(self, seats: List[int]) -> int:  # seats 中 1 表示已坐人、0 表示空座；返回选一个空座时到最近的人的最大距离
        first = last = None  # first、last 记录第一个和最近一个已坐人的下标，None 表示还没有
        d = 0  # d 记录相邻两人之间的最大下标差
        for i, c in enumerate(seats):  # 同时取得下标 i 与座位状态 c
            if c:  # 当前位置已经有人
                if last is not None:  # 前面至少出现过一位已坐人的乘客
                    d = max(d, i - last)  # 用当前与上一位乘客的距离更新最大间隔
                if first is None:  # 这是第一次遇到已坐人
                    first = i  # 记下第一个已坐人的下标，用于计算左端点距离
                last = i  # 更新最近一位已坐人的下标
        return max(first, len(seats) - last - 1, d // 2)  # 三者取最大：坐中间时距离是 d//2，坐左端是 first，坐右端是 n-last-1
