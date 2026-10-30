# 题目：2402. 会议室 III（Meeting Rooms III）
# 思路：按开始时间排序后模拟，用两个小顶堆分别维护空闲会议室编号与「结束时间, 会议室编号」，无空闲时把会议延到最早散场的会议室。
# 时间复杂度：O(m log m + m log n)，排序 m 个会议并做 m 次堆操作；空间复杂度：O(n + m)。
class Solution:  # LeetCode 约定的题解类
    def mostBooked(self, n: int, meetings: List[List[int]]) -> int:  # n：会议室数量；meetings：每个会议的开始与结束时间
        meetings.sort(key=lambda x: x[0])  # 按开始时间升序排序，保证会议按时间先后依次安排
        busy = []  # 忙碌堆：元素为 (结束时间, 会议室编号)，按结束时间最早优先
        idle = list(range(n))  # 空闲堆：初始时所有会议室都空闲
        heapify(idle)  # 把列表整理成小顶堆，保证编号最小的会议室先出堆
        cnt = [0] * n  # cnt[i] 记录第 i 个会议室被使用的次数
        for s, e in meetings:  # 依次安排每一个会议
            while busy and busy[0][0] <= s:  # 结束时间不晚于 s 的会议已经散场
                heappush(idle, heappop(busy)[1])  # 弹出最早散场的会议室，并把它放回空闲堆
            i = 0  # i 记录本次会议分配到的会议室编号
            if idle:  # 还有空闲会议室，直接用编号最小的那个
                i = heappop(idle)  # 取出编号最小的空闲会议室
                heappush(busy, (e, i))  # 会议在原定的 e 时刻结束，登记进忙碌堆
            else:  # 没有空闲会议室，只能等最早散场的会议室空出来
                time_end, i = heappop(busy)  # 取出结束时间最早的会议室及其散场时刻
                heappush(busy, (time_end + e - s, i))  # 整体延后开始，会议时长仍是 e - s
            cnt[i] += 1  # 该会议室的使用次数加一
        ans = 0  # ans 记录使用次数最多的会议室编号
        for i in range(n):  # 遍历所有会议室比使用次数
            if cnt[ans] < cnt[i]:  # 严格大于才更新，次数相同时保留编号更小的会议室
                ans = i  # 更新答案编号
        return ans  # 返回被使用次数最多的会议室编号
