# 题目：253. 会议室 II（Meeting Rooms II）
# 思路：差分数组，开始时刻 +1、结束时刻 -1，再求前缀和的峰值，即任意时刻同时进行的会议数上限。
# 时间复杂度：O(n + m)，m 为最大结束时间；空间复杂度：O(m)，差分数组大小。
class Solution:  # LeetCode 约定的题解类
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:  # intervals：每场会议的 [开始, 结束]，返回所需的最少会议室数量
        m = max(e[1] for e in intervals)  # 求出最大结束时间，确定差分数组长度
        d = [0] * (m + 1)  # 差分数组：下标是时间点，值是占用数的增量
        for l, r in intervals:  # 逐场会议打差分标记
            d[l] += 1  # 开始时刻占用 +1
            d[r] -= 1  # 结束时刻释放 -1
        ans = s = 0  # ans 存峰值（最少房间数），s 存当前占用数
        for v in d:  # 按时间顺序做前缀和
            s += v  # 累加得到该时刻的占用数
            ans = max(ans, s)  # 更新峰值
        return ans  # 峰值即所需最少会议室数
