# 题目：4012. 统计每个班次结束后的未完成任务数（Count of Unfinished Tasks After Each Shift）
# 思路：用前缀和 s 表示前 i 个任务的总工时；每个班次先看能否做完当前任务，能做完就在前缀和上二分定位停在哪个任务、并处理「做完一整轮则从头再来」的情况；未完成任务数恒为 m - i。
# 时间复杂度：O((m + n) log m)，每个班次至多二分一次；空间复杂度：O(m + n)，前缀和数组与答案数组。
class Solution:  # LeetCode 约定的题解类
    def countTasks(self, tasks: List[int], shifts: List[int]) -> List[int]:  # tasks：每个任务的工时；shifts：每个班次的工时；返回每个班次结束后的未完成任务数
        m, n = len(tasks), len(shifts)  # m 为任务数，n 为班次数
        s = list(accumulate(tasks, initial=0))  # 前缀和：s[i] 表示前 i 个任务的总工时（initial=0 让 s[0] = 0）
        ans = [0] * n  # ans[j] 记录第 j 个班次结束后的未完成任务数
        i = cur = 0  # i 是当前任务下标，cur 是该任务上已完成的工时
        for j in range(n):  # 依次处理每个班次
            if shifts[j] < tasks[i] - cur:  # 班次工时不足以做完当前任务
                cur += shifts[j]  # 把整个班次的工时都花在当前任务上
                ans[j] = m - i  # 未完成任务数保持不变
            else:  # 班次工时足以做完当前任务，可能还继续往后做
                t = shifts[j] - (tasks[i] - cur)  # 扣掉做完当前任务所需工时后，剩余的班次工时
                if t >= s[-1] - s[i + 1]:  # 剩余工时足以做完一整轮（i 之后的所有任务）
                    i = cur = 0  # 一轮做完，下标与已完成工时同时归零
                else:  # 剩余工时不足以做完一整轮，用二分定位停在哪一个任务
                    l, r = i + 1, m  # 二分区间为 [i + 1, m]
                    while l < r:  # 二分查找
                        mid = (l + r) >> 1  # 取中点
                        if t < s[mid + 1] - s[i + 1]:  # 剩余工时不足以做完到 mid 为止的任务
                            r = mid  # 收缩右边界
                        else:  # 剩余工时足够做完到 mid 为止
                            l = mid + 1  # 收缩左边界
                    cur = t - (s[l] - s[i + 1])  # 新任务上已完成的工时
                    i = l  # 更新当前任务下标
                    ans[j] = m - i  # 记录该班次结束后的未完成任务数
        return ans  # 返回每个班次结束后的未完成任务数
