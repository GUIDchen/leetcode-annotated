# 题目：759. 员工空闲时间（Employee Free Time）——困难（付费题）
# 思路：把所有员工的工作区间摊平并按 (起点, 终点) 排序，先合并重叠区间，再取相邻合并段之间的空隙 (前一段 end, 后一段 start) 作为公共空闲时间。
# 时间复杂度：O(N log N)，N 为区间总数，主要开销是排序；空间复杂度：O(N)，摊平列表与合并结果各占 O(N)。
"""
# Definition for an Interval.
class Interval:
    def __init__(self, start: int = None, end: int = None):
        self.start = start
        self.end = end
"""


class Solution:  # LeetCode 约定的题解类
    def employeeFreeTime(self, schedule: "[[Interval]]") -> "[Interval]":  # schedule 是每位员工各自的、已按起点排好序的工作区间
        intervals = []  # 用来把所有员工的工作区间摊平到同一个列表里
        for e in schedule:  # 遍历每位员工
            intervals.extend(e)  # 把该员工的区间整段追加到末尾
        intervals.sort(key=lambda x: (x.start, x.end))  # 先按起点升序，起点相同再按终点升序
        merged = [intervals[0]]  # 用第一个区间初始化合并结果
        for x in intervals[1:]:  # 顺序扫描其余区间
            if merged[-1].end < x.start:  # 与上一段完全不相交
                merged.append(x)  # 另起一段
            else:  # 有重叠，需要合并
                merged[-1].end = max(merged[-1].end, x.end)  # 把右端点扩展到更远的一侧
        ans = []  # 收集公共空闲区间
        for a, b in pairwise(merged):  # 依次取相邻的两个合并段，中间就是所有人的公共空闲
            ans.append(Interval(a.end, b.start))  # 空隙就是 (前一段终点, 后一段起点)
        return ans  # 返回按时间升序排列的空闲区间
