# 题目：2323. 完成所有工作的最短时间 II（Find Minimum Time to Finish All Jobs II）
# 核心思路：排序后按「小活配产能小的工人」一一配对，每人所需天数为 jobs[i] / workers[i] 向上取整，答案取最大值。
# 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(1)，除排序内部开销外只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimumTime(self, jobs: List[int], workers: List[int]) -> int:  # jobs：各工作耗时；workers：各工人每日产能
        jobs.sort()  # 工作按耗时升序排列
        workers.sort()  # 工人按产能升序排列
        return max((a + b - 1) // b for a, b in zip(jobs, workers))  # 一一配对后向上取整求天数，取最大值作为最短完成时间
