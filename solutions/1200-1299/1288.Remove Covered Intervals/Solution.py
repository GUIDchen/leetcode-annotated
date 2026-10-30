# 题目：1288. 删除被覆盖区间（Remove Covered Intervals）
# 核心思路：先按左端点升序、左端点相同时右端点降序排序，再顺序扫描；右端点超过历史最大值的区间才没被覆盖。
# 时间复杂度：O(n log n)，瓶颈在排序，扫描为 O(n)；空间复杂度：O(1)，只用常数个变量（不计排序自身开销）。
class Solution:  # LeetCode 约定的题解类
    def removeCoveredIntervals(self, intervals: List[List[int]]) -> int:  # 题解方法对外可见
        intervals.sort(key=lambda x: (x[0], -x[1]))  # intervals 是若干闭区间，返回删除「被其它区间完全覆盖」的区间后剩下的个数
        ans = 0  # C++20 的 ranges::sort：左端点升序；左端点相同时右端点降序，保证大区间排在小区间前面
        pre = -inf  # 排序比较器：左端点小者在前；左端点相同时右端点大者在前
        for _, cur in intervals:  # 排序调用结束
            if cur > pre:  # ans 记录保留的区间数；pre 记录已处理区间的最大右端点，初值取 int 最小值
                ans += 1  # 按排序结果依次遍历每个区间
                pre = cur  # cur 是当前区间的右端点
        return ans  # 右端点比历史最大值更靠右，说明它不可能被之前的任何区间覆盖
