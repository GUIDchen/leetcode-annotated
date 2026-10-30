# 题目：56. 合并区间（Merge Intervals）
# 思路：排序 + 贪心。先按左端点排序让重叠区间相邻，再线性扫描，用一个「待合并区间」边扩展边收集。
# 时间复杂度：O(n log n)，主要花在排序上；空间复杂度：O(log n) 的排序栈（不计返回结果）。
class Solution:  # LeetCode 约定的题解类
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:  # intervals 为若干闭区间，返回合并所有重叠区间后的结果
        intervals.sort()  # 原地按左端点（再按右端点）升序排序，使重叠区间相邻
        ans = []  # 存放合并后的结果
        st, ed = intervals[0]  # st、ed 是当前待合并区间的左右端点，用第一个区间初始化
        for s, e in intervals[1:]:  # 从第二个区间开始，解包成左右端点 s、e
            if ed < s:  # 待合并区间的右端点小于当前左端点，说明两者不相交
                ans.append([st, ed])  # 把已经确定的待合并区间收进答案
                st, ed = s, e  # 把当前区间换成新的待合并区间
            else:  # 否则两者相交（或相接）
                ed = max(ed, e)  # 相交时右端点取较大者，相当于把当前区间并入待合并区间
        ans.append([st, ed])  # 循环结束后最后一个待合并区间还没有收集，补上
        return ans  # 返回合并结果
