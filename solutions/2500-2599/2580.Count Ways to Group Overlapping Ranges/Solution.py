# 题目：2580. 统计将重叠区间合并成组的方案数（Count Ways to Group Overlapping Ranges）
# 思路：按左端点排序后顺序合并相交的区间，得到 cnt 个互不相交的组；每组可归入左侧或右侧集合，答案就是 2^cnt mod (1e9+7)。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，除输入外只用常数个变量（排序额外开销可视为 O(log n)）。
class Solution:  # LeetCode 约定的题解类
    def countWays(self, ranges: List[List[int]]) -> int:  # ranges 是若干闭区间，返回合并分组后的方案数
        ranges.sort()  # 按左端点（相同时按右端点）排序，方便顺序判断是否相交
        cnt, mx = 0, -1  # cnt 为合并后的组数；mx 为当前组覆盖到的最右端点
        for start, end in ranges:  # 依次处理每个区间，同时解包左右端点
            if start > mx:  # 左端点超过 mx，说明与当前组不相交，必须另起一组
                cnt += 1  # 组数加一
            mx = max(mx, end)  # 更新当前组覆盖的最右端点
        mod = 10**9 + 7  # 取模用的大质数
        return pow(2, cnt, mod)  # 每组可任选归入哪一侧，共 2^cnt 种方案；内置 pow 支持模幂，天然防溢出
