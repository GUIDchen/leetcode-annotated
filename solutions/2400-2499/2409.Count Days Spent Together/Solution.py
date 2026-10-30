# 题目：2409. 统计共同度过的日子数（Count Days Spent Together）
# 思路：把 MM-DD 格式的日期换算成当年的第几天，两人的共同区间就是两个区间的交集，交集天数为 max(0, end - start + 1)。
# 时间复杂度：O(1)，只有常数次字符串与下标操作；空间复杂度：O(1)，只用一张 12 个月的前缀和表。
f = list(accumulate([31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31], initial=0))  # 前缀和：f[i] 表示第 i 个月之前累计的天数（initial=0 让 1 月之前为 0 天）


class Solution:  # LeetCode 约定的题解类
    def countDaysTogether(  # 参数为两人各自的到达日与离开日，格式为 MM-DD
        self, arriveAlice: str, leaveAlice: str, arriveBob: str, leaveBob: str  # 定长日期字符串，直接按字典序比较即可判断先后
    ) -> int:  # 返回共同度过的天数
        start = max(arriveAlice, arriveBob)  # 较大者是较晚的到达日，即交集区间的起点
        end = min(leaveAlice, leaveBob)  # 较小者是较早的离开日，即交集区间的终点
        d1 = f[int(start[:2]) - 1] + int(start[3:])  # 开始日期换算成当年的第几天
        d2 = f[int(end[:2]) - 1] + int(end[3:])  # 结束日期换算成当年的第几天
        return max(d2 - d1 + 1, 0)  # 交集长度即共同天数，区间不相交时取 0
