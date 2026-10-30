# 题目：3986. Number of Elapsed Seconds Between Two Times（3986. 统计起止时间经过的秒数）
# 核心思路：把 HH:MM:SS 换算成从 00:00:00 起的当天总秒数（时×3600 + 分×60 + 秒），结束时刻与开始时刻的秒数相减即为经过的秒数。
# 复杂度：时间 O(1)，空间 O(1)。
class Solution:  # 定义题解类
    def secondsBetweenTimes(self, startTime: str, endTime: str) -> int:  # 返回从 startTime 到 endTime 经过的秒数
        def f(s: str) -> int:  # 内部函数：把 HH:MM:SS 换算成当天的总秒数
            return int(s[:2]) * 3600 + int(s[3:5]) * 60 + int(s[6:])  # 时、分、秒分别换算成秒后相加

        return f(endTime) - f(startTime)  # 两个时刻的当天秒数相减即为经过的秒数
