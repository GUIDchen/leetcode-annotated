# 题目：3502. 到达每个位置的最小费用（Minimum Cost to Reach Every Position）
# 思路：到达位置 i 要么直接付费与 i 交换，要么先付费与某个 j < i 交换再免费向前换位，故答案就是 cost 的前缀最小值。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(n)，除答案数组外只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minCosts(self, cost: List[int]) -> List[int]:  # cost：与每个位置的人换位所需费用，返回到达每个位置的最小总费用
        n = len(cost)  # 位置个数
        ans = [0] * n  # 结果数组，ans[i] 表示到达位置 i 的最小费用
        mi = cost[0]  # 到达位置 0 只能付 cost[0]，先把它作为前缀最小值
        for i, c in enumerate(cost):  # 从左到右扫描每个位置
            mi = min(mi, c)  # 维护前缀最小值：付更便宜的前一个位置，再免费向前走
            ans[i] = mi  # 到达位置 i 的最小费用就是这个前缀最小值
        return ans  # 返回每个位置的最小费用
