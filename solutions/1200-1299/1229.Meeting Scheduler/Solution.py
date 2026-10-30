# 题目：1229. 安排会议日程（Meeting Scheduler）
# 思路：两人空闲时段分别排序后用双指针求交集，每个时刻只检查两个当前区间的重叠长度，不够长就推进结束更早的那个指针。
# 时间复杂度：O(m log m + n log n)，排序占主导；空间复杂度：O(1)，只用双指针与常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minAvailableDuration(  # slots1/slots2：两人的空闲时段；duration：会议时长；返回最早的可行时间段
        self, slots1: List[List[int]], slots2: List[List[int]], duration: int  # 签名续行：两个空闲时段列表与会议时长 duration
    ) -> List[int]:  # ) -> List[int]: 收尾签名并声明返回「开始时间与结束时间」列表
        slots1.sort()  # 把第一个人的时段按开始时间升序排序
        slots2.sort()  # 把第二个人的时段同样排序
        m, n = len(slots1), len(slots2)  # m、n 分别是两人空闲时段的个数
        i = j = 0  # i、j 是两人当前考察的时段下标，都从 0 开始
        while i < m and j < n:  # 两人都还有时段没看完时继续找重叠
            start = max(slots1[i][0], slots2[j][0])  # 重叠区间起点：两个时段开始时间的较大者
            end = min(slots1[i][1], slots2[j][1])  # 重叠区间终点：两个时段结束时间的较小者
            if end - start >= duration:  # 重叠长度足够放下会议
                return [start, start + duration]  # 取这段重叠的前 duration 分钟返回（排序保证最早）
            if slots1[i][1] < slots2[j][1]:  # 结束更早的那个时段不可能再与对方后面的时段重叠
                i += 1  # 第一个人的这个时段结束得更早，看下一个
            else:  # 否则说明第二个人的这个时段结束得更早
                j += 1  # 改看第二个人的下一个时段
        return []  # 所有时段都考察完仍无够长的重叠，返回空列表表示无解
