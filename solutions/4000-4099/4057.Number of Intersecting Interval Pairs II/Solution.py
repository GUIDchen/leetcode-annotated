# 题目：4057. 统计相交区间对 II（Number of Intersecting Interval Pairs II）
# 思路：与 I 完全同构——不相交等价于一个区间的右端点严格小于另一个区间的左端点；把左右端点分别排序，先取 C(n,2)，再按左端点顺序用单调前进的指针统计在其之前就结束的区间个数并扣减；差别只在 n 变大，答案改用 long long（Python 天然支持大整数）承接 C(n,2) 以免溢出。
# 时间复杂度：O(n log n)，主要开销是两次排序；空间复杂度：O(n)，用于存放左右端点数组。
class Solution:  # LeetCode 约定的题解类
    def countIntersectingIntervals(self, intervals: list[list[int]]) -> int:  # intervals：若干闭区间；返回其中相交的区间对数目
        n = len(intervals)  # n 为区间个数，全部区间对共有 C(n,2) 个
        starts = sorted(s for s, _ in intervals)  # 左端点升序、右端点升序，便于用单指针扫描
        ends = sorted(e for _, e in intervals)  # 右端点同样升序
        ans = n * (n - 1) // 2  # 先假设所有区间对都相交（Python 整数无溢出，n 再大也不会溢出）
        i = 0  # i 指向 ends 中第一个“不早于当前起点结束”的位置，只前进不回退
        for start in starts:  # 按左端点从小到大扫描
            while i < n and ends[i] < start:  # 只有 end < start 才算不相交，端点相触仍算相交
                i += 1  # 指针前移，把在 start 之前结束的区间都数进来
            ans -= i  # 这 i 个区间与当前区间两两不相交，从总数中扣除
        return ans  # 返回相交区间对数
