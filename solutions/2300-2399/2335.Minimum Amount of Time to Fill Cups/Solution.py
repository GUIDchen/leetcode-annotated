# 题目：2335. 装满杯子需要的最短总时长（Minimum Amount of Time to Fill Cups）
# 核心思路：每一秒同时给目前剩余最多的两种杯子各倒一杯；升序排序后让 amount[2] 与 amount[1] 同时减一，直到总和为零。
# 时间复杂度：O(sum(amount))，每秒只做一次三元素排序；空间复杂度：O(1)，仅用常数额外变量。
class Solution:  # LeetCode 约定的题解类
    def fillCups(self, amount: List[int]) -> int:  # amount：三种杯子各自还需要的杯数，返回值是最短总秒数
        ans = 0  # ans：已经花费的秒数，也就是最终答案
        while sum(amount):  # 三种杯子需求之和大于 0 就说明还没装满，继续循环
            amount.sort()  # 原地升序排序，使 amount[2] 最大、amount[1] 次大
            ans += 1  # 开始新的一秒，秒数加一
            amount[2] -= 1  # 需求最多的那种杯子倒一杯（需求减一）
            amount[1] = max(0, amount[1] - 1)  # 次多的杯子也倒一杯；减后可能为负，用 max 夹到 0 表示已空
        return ans  # 全部装满，返回所需的最短总时长
