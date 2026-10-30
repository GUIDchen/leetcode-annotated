# 题目：630. 课程表 III（Course Schedule III）
# 思路：按截止时间升序排序，用堆保存已选课程时长（存负数模拟大顶堆）；当前总时长超期时丢掉最长的那门课。
# 时间复杂度：O(n log n)；空间复杂度：O(n)，堆最多存 n 个时长。
class Solution:  # LeetCode 约定的题解类
    def scheduleCourse(self, courses: List[List[int]]) -> int:  # courses[i] = [duration, lastDay]，返回最多能修的课程门数（源码返回 int）
        courses.sort(key=lambda x: x[1])  # 按截止时间 x[1] 升序排序，优先考虑先到期的课
        pq = []  # 堆：存已选课程时长的相反数，heappush/heappop 由判题环境提供
        s = 0  # 已选课程总时长，即当前时间
        for duration, last in courses:  # 按截止时间从早到晚逐门决定
            heappush(pq, -duration)  # 压入负时长，小顶堆的堆顶就是绝对值最大、也就是时长最长的那门课
            s += duration  # 总时长加上这门课
            while s > last:  # 总时长超过该课截止时间，说明必须淘汰一门
                s += heappop(pq)  # 弹出堆顶（负数），s 加上它等价于减去最长时长
        return len(pq)  # 堆的大小就是最多能修的课程数
