# 题目：1665. 完成所有任务的最少初始能量（Minimum Initial Energy to Finish Tasks）
# 思路：按 (最低需求 m - 实际消耗 a) 升序排序后依次执行；当前剩余能量不足 m 时补齐差额并累加到答案。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，sorted 会返回一个新列表。
class Solution:  # LeetCode 约定的题解类
    def minimumEffort(self, tasks: List[List[int]]) -> int:  # tasks[i] = [实际消耗 a, 最低启动能量 m]，返回最少初始能量
        ans = cur = 0  # ans：需补足的初始能量总和；cur：当前剩余能量
        for a, m in sorted(tasks, key=lambda x: x[0] - x[1]):  # 按 (a - m) 升序执行：消耗相对门槛更大的任务先做，预支的能量最少
            if cur < m:  # 当前能量不足以启动本任务
                ans += m - cur  # 差额必须体现在初始能量里，累加到 ans
                cur = m  # 补足后当前能量变成门槛 m
            cur -= a  # 完成任务，扣掉实际消耗
        return ans  # 返回最少初始能量
