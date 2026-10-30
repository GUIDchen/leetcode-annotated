# 题目：2054. 两个最好的不重叠活动（Two Best Non-Overlapping Events）
# 思路：按开始时间排序后预处理后缀最大价值 f；枚举第一个活动，二分找第一个开始时间严格大于其结束时间的活动，用 f 取第二个活动的最优值。
# 时间复杂度：O(n log n)，排序加每个活动一次二分；空间复杂度：O(n)，后缀最大值数组。
class Solution:  # 题解类
    def maxTwoEvents(self, events: List[List[int]]) -> int:  # events[i] = [开始, 结束, 价值]
        events.sort()  # 按开始时间升序排序
        n = len(events)  # 活动个数
        f = [events[-1][2]] * n  # f[i] 表示从第 i 个活动开始到末尾的最大价值，先全用最后一个活动的值
        for i in range(n - 2, -1, -1):  # 从倒数第二个活动开始往前递推
            f[i] = max(f[i + 1], events[i][2])  # 不选第 i 个（f[i+1]）与选它（events[i][2]）取较大者
        ans = 0  # 答案至少为 0
        for _, e, v in events:  # 枚举第一个活动：e 是结束时间，v 是价值
            idx = bisect_right(events, e, key=lambda x: x[0])  # 二分找第一个开始时间严格大于 e 的活动下标
            if idx < n:  # 后面还有可以接的活动
                v += f[idx]  # 叠加后续最大价值
            ans = max(ans, v)  # 更新答案
        return ans  # 返回最多两个活动的最大价值和
