# 题目：252. 会议室（Meeting Rooms）
# 思路：先按开始时间排序，再用 pairwise 检查相邻两场会议的结束/开始时间是否冲突。
# 时间复杂度：O(n log n)，排序开销；空间复杂度：O(1)，原地排序，pairwise 为迭代器。
class Solution:  # LeetCode 约定的题解类
    def canAttendMeetings(self, intervals: List[List[int]]) -> bool:  # intervals：每个元素是 [开始时间, 结束时间]，判断能否参加全部会议
        intervals.sort()  # 按开始时间升序排序（元素是 list，默认按字典序比较，即先比开始时间）
        return all(a[1] <= b[0] for a, b in pairwise(intervals))  # pairwise 生成相邻两场的组合；只要每段前一场的结束时间不晚于后一场的开始时间，就没有重叠
