# 题目：2895. 最小处理时间（Minimum Processing Time）
# 思路：两个数组都升序排序，最早空闲的处理器领走当前最长的 4 个任务中的最大值，贪心使完成时间的最大值最小。
# 时间复杂度：O(n log n + m log m)，开销来自两次排序；空间复杂度：O(1)，只用了常数个变量（不计排序内部开销）。
class Solution:  # LeetCode 约定的题解类
    def minProcessingTime(self, processorTime: List[int], tasks: List[int]) -> int:  # processorTime：各处理器开始时间；tasks：任务耗时
        processorTime.sort()  # 处理器时间升序，最先空闲的排在最前
        tasks.sort()  # 任务时间升序，最长的任务排在最后
        ans = 0  # ans：所有任务完成时间的上界，初始为 0
        i = len(tasks) - 1  # 当前最长任务的下标，从末尾开始
        for t in processorTime:  # 按处理器时间从小到大依次分配
            ans = max(ans, t + tasks[i])  # 该处理器承担 4 个任务中最长的一个，更新完成时间上界
            i -= 4  # 一个处理器一次处理 4 个任务，任务下标前移 4 位
        return ans  # 返回所有任务完成所需的最小时间
