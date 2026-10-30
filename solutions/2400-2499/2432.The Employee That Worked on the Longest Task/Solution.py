# 题目：2432. 处理用时最长的那个任务的员工（The Employee That Worked on the Longest Task）
# 思路：日志按完成时刻升序给出，相邻两条的时间差即本次任务用时；遍历时维护最长用时与对应员工编号。
# 时间复杂度：O(n)，只扫一遍日志；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def hardestWorker(self, n: int, logs: List[List[int]]) -> int:  # n：员工总数；logs：每条日志为 [员工编号, 任务完成时刻]
        last = mx = ans = 0  # last：上一条日志的完成时刻；mx：最长用时；ans：答案员工编号
        for uid, t in logs:  # 逐条解包日志，uid 是员工编号，t 先取任务完成时刻
            t -= last  # 用当前时刻减去上一条完成时刻，得到本次任务实际用时
            if mx < t or (mx == t and ans > uid):  # 用时更长，或用时相同但员工编号更小（题目要求编号最小）
                ans, mx = uid, t  # 同时更新答案员工编号与最长用时
            last += t  # 累加耗时，把 last 推进到当前日志的完成时刻，供下一轮使用
        return ans  # 返回用时最长的员工编号
