# 4068. 考虑空闲时间的会议最大收益  Maximize Meeting Earnings with Idle Gaps
# 核心思路：按结束时间排序后做 DP，pre_max 记录“收益-结束时间”的前缀最大值，空闲时长可作为额外收益计入。
# 复杂度：时间 O(n log n)，空间 O(n)。

class Solution:
    def maxEarnings(self, meetings: list[list[int]]) -> int:  # 返回可获得的最大总收益
        n = len(meetings)  # 会议数量
        meetings.sort(key=lambda x: x[1])  # 按会议结束时间升序排序

        pre_max = [-inf] * (n + 1)  # pre_max[i] 表示前 i 场会议中“收益-结束时间”的最大值
        ans = 0  # 记录最大总收益

        for i, (start, end, revenue) in enumerate(meetings):  # 依次把第 i 场会议作为最后一场
            val = revenue  # 只选当前会议时的收益
            if start >= meetings[0][1]:  # 起始时间不早于最早结束的会议，说明可能存在可衔接的前驱
                j = bisect_right(meetings, start, hi=i, key=lambda x: x[1])  # 在前 i 场中找结束时间不晚于 start 的会议数量
                val += pre_max[j] + start  # 前驱最优收益加上这段空闲时长带来的收益

            ans = max(ans, val)  # 更新最大总收益
            pre_max[i + 1] = max(pre_max[i], val - end)  # 递推前缀最大值，扣除结束时间供后续衔接使用

        return ans  # 返回最大总收益
