# 题目：1124. 表现良好的最长时间段（Longest Well-Performing Interval）
# 思路：把「工时大于 8 小时」记为 +1、其余记为 -1，问题转化为求「区间和为正」的最长连续子数组；用哈希表记录每个前缀和首次出现的最小下标，当前前缀和 s>0 时整段合法，否则用 s-1 的首次出现位置把区间拉到最长。
# 时间复杂度：O(n)，只需一次线性扫描；空间复杂度 O(n)，哈希表最多保存 n 个不同前缀和。
class Solution:  # LeetCode 约定的题解类
    def longestWPI(self, hours: List[int]) -> int:  # hours：每天工作时长；返回表现良好时间段的最长长度
        ans = s = 0  # ans：答案长度；s：前缀和（>8 记 +1，否则记 -1）
        pos = {}  # pos：哈希表，键是前缀和，值是它第一次出现的下标
        for i, x in enumerate(hours):  # 同时枚举下标 i 与当天时长 x
            s += 1 if x > 8 else -1  # 更新前缀和
            if s > 0:  # 前缀和为正，说明 [0, i] 整段都表现良好
                ans = i + 1  # 整段长度即为候选答案
            elif s - 1 in pos:  # 否则看 s-1 是否出现过，出现过就能取到和为正的最长区间
                ans = max(ans, i - pos[s - 1])  # 区间 (pos[s-1], i] 之和为 1，用它更新答案
            if s not in pos:  # 前缀和只在第一次出现时记录
                pos[s] = i  # 越靠前越能拉长区间
        return ans  # 返回最长表现良好时间段的长度
