# 题目：3893. 最大重叠区间团队规模（Maximum Team Size with Overlapping Intervals）
# 思路：枚举每个区间作为“与所有人互动的那个人”，能与它重叠的区间数 = 起点 ≤ r 的个数 − 终点 < l 的个数，用排序后的两个数组二分得到。
# 时间复杂度：O(n log n)，主要是两次排序与 n 次二分；空间复杂度：O(n)，存放区间对。
class Solution:  # LeetCode 约定的题解类
    def maximumTeamSize(self, startTime: list[int], endTime: list[int]) -> int:  # startTime / endTime：每个员工的开始与结束时间
        intervals = list(zip(startTime, endTime))  # 先把区间成对保存，后面排序会打乱下标
        startTime.sort()  # 对开始时间排序，便于统计“起点 ≤ x”的个数
        endTime.sort()  # 对结束时间排序，便于统计“终点 ≤ x”的个数
        ans = 0  # 答案：团队最大规模
        for l, r in intervals:  # 枚举作为“中心”的那个区间
            i = bisect_right(endTime, l - 1)  # 终点 ≤ l-1 的区间整体在左侧，不重叠，i 即为这类区间个数
            j = bisect_right(startTime, r)  # 起点 ≤ r 的区间个数 j
            ans = max(ans, j - i)  # j - i 即与当前区间重叠的区间数（含自身）
        return ans  # 返回最大团队规模
