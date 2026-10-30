# 题目：3709. Design Exam Scores Tracker（3709. 设计考试分数记录器）
# 核心思路：记录的时间天然严格递增，因此用 times 存时间、pre 存前缀和；查询时用二分找出两个端点下标，前缀和相减即得闭区间总分。
# 复杂度：record 为 O(1)，totalScore 为 O(log n)，空间 O(n)。
class ExamTracker:  # 定义考试分数记录器类

    def __init__(self):  # 构造函数：初始化两个哨兵元素
        self.times = [0]  # 下标 0 放时间哨兵 0，保证二分查找有下界
        self.pre = [0]  # 下标 0 放前缀和哨兵 0

    def record(self, time: int, score: int) -> None:  # 记录一条成绩：time 递增，score 为本次得分
        self.times.append(time)  # 时间天然有序，直接追加到末尾
        self.pre.append(self.pre[-1] + score)  # 前缀和累加，pre[i] 表示前 i 条记录的总分

    def totalScore(self, startTime: int, endTime: int) -> int:  # 返回闭区间 [startTime, endTime] 内的总分
        l = bisect_left(self.times, startTime) - 1  # 第一个 >= startTime 的下标减一，即时间 < startTime 的记录条数
        r = bisect_left(self.times, endTime + 1) - 1  # 第一个 >= endTime + 1 的下标减一，即时间 <= endTime 的记录条数
        return self.pre[r] - self.pre[l]  # 前缀和相减得到区间总分


# Your ExamTracker object will be instantiated and called as such:
# obj = ExamTracker()
# obj.record(time,score)
# param_2 = obj.totalScore(startTime,endTime)
