# 题目：495. 提莫攻击（Teemo Attacking）
# 思路：第一次攻击固定贡献 duration 秒，之后每相邻两次攻击只新增 min(duration, 间隔) 秒，逐段累加即得总中毒时长。
# 时间复杂度：O(n)，只需遍历一次时间序列；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def findPoisonedDuration(self, timeSeries: List[int], duration: int) -> int:  # timeSeries 是递增的攻击时间点，duration 是每次中毒持续的秒数
        ans = duration  # 先用第一次攻击的完整中毒时长打底
        for a, b in pairwise(timeSeries):  # pairwise 依次给出相邻的两次攻击时间 (a, b)
            ans += min(duration, b - a)  # 间隔大于 duration 时两段中毒不重叠（取 duration），否则取实际间隔
        return ans  # 返回累计的中毒总秒数
