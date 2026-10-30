# 题目：1751. 最多可以参加的会议数目 II（Maximum Number of Events That Can Be Attended II）
# 核心思路：会议按开始时间排序后记忆化搜索 dfs(i, k)，每个会议要么跳过、要么参加并二分跳到第一个开始时间晚于其结束时间的会议，两种取较大值。
# 时间复杂度：O(n·k·log n)，共 n·k 个状态、每次二分后继；空间复杂度：O(n·k)，缓存表。
class Solution:  # LeetCode 约定的题解类
    def maxValue(self, events: List[List[int]], k: int) -> int:  # events 每项是 [开始, 结束, 价值]，k 是最多参加的会议数
        @cache  # cache 自动记忆化，避免同一 (i, k) 状态重复递归
        def dfs(i: int, k: int) -> int:  # i 是当前考虑的会议下标，k 是剩余可参加次数
            if i >= len(events):  # 边界：所有会议都考虑完
                return 0  # 没有会议可选，收益为 0
            _, ed, val = events[i]  # 拆出当前会议的结束时间与价值（开始时间排序后不需要再用）
            ans = dfs(i + 1, k)  # 决策一：跳过当前会议，下标后移、名额不变
            if k:  # 名额还有剩余才能考虑参加
                j = bisect_right(events, ed, lo=i + 1, key=lambda x: x[0])  # 二分找第一个开始时间大于 ed 的会议，即不冲突的下一个会议下标
                ans = max(ans, dfs(j, k - 1) + val)  # 决策二：参加当前会议，获得价值并消耗一个名额
            return ans  # 两种决策的较大值即为该状态答案

        events.sort()  # 先按开始时间排序，二分才有单调性
        return dfs(0, k)  # 从第一个会议、k 个名额开始搜索
