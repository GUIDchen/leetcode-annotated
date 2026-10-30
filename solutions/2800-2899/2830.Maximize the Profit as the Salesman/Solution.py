# 题目：2830. 销售利润最大化（Maximize the Profit as the Salesman）
# 思路：按报价结束位置排序后做线性 DP，f[i] 表示前 i 条报价的最大利润；转移时用二分找出结束位置不晚于当前报价起点的报价条数 j，在「不选」与「选」当前报价之间取较大值。
# 时间复杂度：O(m log m)，m 为报价条数（排序 + 每条报价一次二分）；空间复杂度：O(m)，f 与 g 两个数组。
class Solution:  # LeetCode 约定的题解类
    def maximizeTheProfit(self, n: int, offers: List[List[int]]) -> int:  # n：房屋数量（未直接使用）；offers：每项为 [起点, 终点, 利润]
        offers.sort(key=lambda x: x[1])  # 按结束位置升序排序，让 DP 可以按结束时间从前往后推进
        f = [0] * (len(offers) + 1)  # f[i]：只考虑前 i 条报价时的最大利润，全部初始化为 0
        g = [x[1] for x in offers]  # 抽出所有结束位置，构成与 offers 同序的单调不减数组，供二分使用
        for i, (s, _, v) in enumerate(offers, 1):  # 从 1 开始编号；s 是起点、v 是利润，中间那项结束位置用 _ 占位丢弃
            j = bisect_left(g, s)  # 第一个结束位置 >= 起点 s 的下标 j，前 j 条报价都不会与当前报价重叠
            f[i] = max(f[i - 1], f[j] + v)  # 取较大者：不做当前报价，或做当前报价（前 j 条最优 + 本条利润）
        return f[-1]  # 考虑全部报价后的最大利润就是答案
