# 题目：739. 每日温度（Daily Temperatures）
# 思路：从右往左维护「温度严格递减」的下标单调栈，栈顶即右侧第一个更高温度的日子，直接算出等待天数。
# 时间复杂度：O(n)，每个下标最多入栈、出栈各一次；空间复杂度：O(n)，栈与答案数组各占 O(n)。
class Solution:  # LeetCode 约定的题解类
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:  # temperatures：每天的温度数组，返回每天需要等待的天数
        stk = []  # 单调栈，存下标；栈内自底向顶对应温度严格递减
        n = len(temperatures)  # 总天数
        ans = [0] * n  # 答案数组：默认 0 表示之后没有更高温度
        for i in range(n - 1, -1, -1):  # 从最后一天往前遍历到第 0 天
            while stk and temperatures[stk[-1]] <= temperatures[i]:  # 栈顶温度不高于当前温度，它不会再是任何更左位置的答案，弹出
                stk.pop()  # 弹出被淘汰的下标
            if stk:  # 栈非空说明右侧存在第一个更高温度
                ans[i] = stk[-1] - i  # 栈顶下标减当前下标即等待天数
            stk.append(i)  # 当前下标入栈，成为更左位置的候选
        return ans  # 返回每天的等待天数
