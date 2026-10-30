# 题目：435. 无重叠区间（Non-overlapping Intervals）
# 思路：贪心——按右端点升序排序，尽量保留右端点小的区间：能与上一个保留区间接上就保留，接不上就必须移除它，这样保留的区间最多、移除的最少。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1) 额外空间（排序本身的开销除外）。
class Solution:  # LeetCode 约定的题解类
    def eraseOverlapIntervals(self, intervals: List[List[int]]) -> int:  # 返回最少需要移除的区间数，使剩下的区间两两互不重叠
        intervals.sort(key=lambda x: x[1])  # 按右端点升序原地排序，key 取每个区间的第二个元素
        ans = len(intervals)  # 先假设所有区间都要移除，之后每保留一个就减 1
        pre = -inf  # 上一个被保留区间的右端点，初始为负无穷以保证第一个区间一定能接上
        for l, r in intervals:  # 按右端点从小到大依次做贪心判断，同时解包出左右端点
            if pre <= l:  # 与上一个保留区间不重叠（端点刚好相接也算不重叠）
                ans -= 1  # 该区间可以保留，需要移除的数量减 1
                pre = r  # 更新已保留区间的右端点
        return ans  # 剩余的 ans 就是必须移除的最少区间数
