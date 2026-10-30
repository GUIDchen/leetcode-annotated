# 题目：1109. 航班预订统计（Corporate Flight Bookings）
# 思路：差分数组，区间 [first, last] 加 seats 只修改两个端点，最后用 accumulate 做前缀和一次还原。
# 时间复杂度：O(n + m)，m 为预订条数；空间复杂度：O(n)，ans 保存 n 个差分值。
class Solution:  # LeetCode 约定的题解类
    def corpFlightBookings(self, bookings: List[List[int]], n: int) -> List[int]:  # bookings 每项是 {first, last, seats}，n 是航班总数
        ans = [0] * n  # 差分数组，下标 0 对应航班 1
        for first, last, seats in bookings:  # 逐条拆出区间起点、终点与座位数
            ans[first - 1] += seats  # 差分：区间起点处加上 seats
            if last < n:  # 右端点之后还有航班时才需要反向抵消
                ans[last] -= seats  # 差分：右端点的下一个位置减去 seats，使区间外不受影响
        return list(accumulate(ans))  # 前缀和还原每个航班的真实预订数（accumulate 来自 itertools）
