# 题目：757. 设置交集大小至少为2（Set Intersection Size At Least Two）——困难
# 思路：按 (右端点升序, 左端点降序) 排序后贪心：用 s、e 记录目前已选的最大两个数，每个区间缺几个数就补几个。
# 时间复杂度：O(n log n)，主要开销是排序；空间复杂度：O(1)（不算排序自身），只用了常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def intersectionSizeTwo(self, intervals: List[List[int]]) -> int:  # intervals 是所有区间的列表
        intervals.sort(key=lambda x: (x[1], -x[0]))  # 右端点升序；右端点相同时左端点降序（短区间优先）
        s = e = -1  # s、e 是目前已选的两个最大数字（初值 -1 表示还没选任何数）
        ans = 0  # 已选入交集的数字个数
        for a, b in intervals:  # 按排序后的顺序逐个处理区间
            if a <= s:  # 当前两个数字都落在区间内，无需再补
                continue
            if a > e:  # 两个数字都没进入区间，至少要补 2 个
                ans += 2  # 补两个数
                s, e = b - 1, b  # 为兼顾后面的区间，尽量选靠右的数：次大值 b-1、最大值 b
            else:  # 只有 e 落在区间内，只需再补 1 个
                ans += 1  # 补一个数
                s, e = e, b  # 原来的最大值变成次大值，再选当前右端点作为新的最大值
        return ans  # 返回至少需要选择的数字个数
