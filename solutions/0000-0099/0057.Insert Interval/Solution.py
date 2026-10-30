# 题目：57. 插入区间（Insert Interval）
# 思路：把新区间追加进数组，再复用「合并区间」的做法：先按左端点排序，然后线性扫描合并相邻重叠区间。
# 时间复杂度：O(n log n)，主要由排序决定；空间复杂度：O(log n) 的排序栈（不计返回结果）。
class Solution:  # LeetCode 约定的题解类
    def insert(
        self, intervals: List[List[int]], newInterval: List[int]
    ) -> List[List[int]]:  # intervals 为已按左端点升序排列的不重叠区间，newInterval 待插入；返回插入并合并后的结果
        def merge(intervals: List[List[int]]) -> List[List[int]]:  # 内层函数：把相互重叠的区间合并成互不重叠的结果
            intervals.sort()  # 原地按左端点升序排序，保证可能重叠的区间相邻
            ans = [intervals[0]]  # 结果列表，用第一个区间初始化
            for s, e in intervals[1:]:  # 从第二个区间开始，解包成左右端点 s、e
                if ans[-1][1] < s:  # 结果末尾区间的右端点小于当前左端点，说明两者不相交
                    ans.append([s, e])  # 不相交：当前区间另起一段放进结果
                else:  # 否则两者相交（或相接）
                    ans[-1][1] = max(ans[-1][1], e)  # 相交：把末尾区间的右端点延长到两者中较大的那个
            return ans  # 返回合并后的区间列表

        intervals.append(newInterval)  # 把新区间追加到末尾（此时顺序可能被破坏）
        return merge(intervals)  # 交给 merge 统一排序并合并，避免两套逻辑
