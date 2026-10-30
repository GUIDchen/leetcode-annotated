# 题目：3169. 无需开会的工作日（Count Days Without Meetings）
# 思路：会议区间按开始日排序，用 last 记录已被覆盖的最晚日期；遍历时若 st > last 就把空档 st-last-1 累加，最后补上 last 之后到第 days 天的空档。
# 时间复杂度：O(n log n)，排序开销；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def countDays(self, days: int, meetings: List[List[int]]) -> int:  # days 是总天数，meetings 是形如 [开始日, 结束日] 的区间列表，返回无需开会的天数
        meetings.sort()  # 按开始日升序排序，使区间从左到右依次处理
        ans = last = 0  # ans 累计无会议天数；last 是已覆盖区间的最右端（0 表示尚未覆盖任何一天）
        for st, ed in meetings:  # 依次取出每个区间的左右端点
            if last < st:  # 区间开始日晚于已覆盖范围，说明中间存在空档
                ans += st - last - 1  # 空档长度 = st - last - 1，两头都是会议日所以不计
            last = max(last, ed)  # 合并区间：last 取右端点更大者，保持为已覆盖的最晚日期
        ans += days - last  # 收尾：last 之后直到第 days 天也都没有会议
        return ans  # 返回无需开会的工作日总数
