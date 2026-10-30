# 题目：256. 粉刷房子（Paint House）
# 思路：动态规划。a/b/c 表示最后一栋刷成红/绿/蓝的最小累计花费，每栋用上一轮另外两色的较小值转移，元组赋值保证右边全用旧值。
# 时间复杂度：O(n)，n 为房子数；空间复杂度：O(1)，只用三个滚动变量。

class Solution:  # LeetCode 约定的题解类
    def minCost(self, costs: List[List[int]]) -> int:  # costs[i] 是第 i 栋房子三种颜色的花费
        a = b = c = 0  # 第一栋之前，红/绿/蓝三种刷法的累计花费都是 0
        for ca, cb, cc in costs:  # 逐栋处理，ca/cb/cc 为本栋刷红/绿/蓝的花费
            a, b, c = min(b, c) + ca, min(a, c) + cb, min(a, b) + cc  # 元组赋值：右边全部用旧值算，刷某色则上一栋只能刷另外两色
        return min(a, b, c)  # 最后一栋取三种刷法中的最小总花费
