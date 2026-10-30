# 题目：2406. 将区间分为最少组数（Divide Intervals Into Minimum Number of Groups）
# 思路：按左端点升序处理区间，用小根堆维护各组的最晚结束时间，能复用空闲组就复用。
# 时间复杂度：O(n log n)，排序加每次堆操作；空间复杂度：O(n)，堆最多保存 n 个结束时间。
class Solution:  # LeetCode 约定的题解类
    def minGroups(self, intervals: List[List[int]]) -> int:  # intervals：若干闭区间，返回把它们划分成互不重叠的组所需的最少组数
        q = []  # 小根堆：保存当前每个组中最晚的结束时间，堆顶是最早结束的组
        for left, right in sorted(intervals):  # 按左端点升序逐个处理区间
            if q and q[0] < left:  # 堆非空且结束最早的组已经早于当前左端点，说明该组空闲可复用
                heappop(q)  # 弹出这一组的旧结束时间，相当于把它挪给当前区间
            heappush(q, right)  # 把当前区间的右端点作为该组新的结束时间
        return len(q)  # 堆的大小就是同时活跃的组数，也就是最少需要的组数
