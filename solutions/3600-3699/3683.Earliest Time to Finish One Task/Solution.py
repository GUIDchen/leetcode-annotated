# 3683. 完成一个任务的最早时间 / Earliest Time to Finish One Task
# 核心思路：每个任务的完成时刻等于开始时刻加耗时，取所有任务完成时刻的最小值即可
# 时间复杂度 O(n)，空间复杂度 O(1)
class Solution:  # 题解类
    def earliestTime(self, tasks: List[List[int]]) -> int:  # 返回最早完成一个任务的时刻
        return min(s + t for s, t in tasks)  # s 为开始时刻，t 为耗时，取所有完成时刻的最小值
