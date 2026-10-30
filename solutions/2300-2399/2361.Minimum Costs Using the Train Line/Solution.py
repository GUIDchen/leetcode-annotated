# 题目：2361. 乘坐火车路线的最少费用（Minimum Costs Using the Train Line）
# 思路：线性 DP，f[i]、g[i] 分别表示到第 i 站时人在普通线 / 快线上的最小累计费用，逐站转移后取较小值。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(n)，两个 DP 数组加一个答案数组。
class Solution:  # LeetCode 约定的题解类
    def minimumCosts(
        self, regular: List[int], express: List[int], expressCost: int
    ) -> List[int]:  # regular、express：两趟车逐站票价；expressCost：换乘快线的额外费用
        n = len(regular)  # n 为站数
        f = [0] * (n + 1)  # f[i]：到达第 i 站后仍停留在普通线上的最小花费
        g = [inf] * (n + 1)  # g[i]：到达第 i 站后停留在快线上的最小花费（inf 表示不可达）
        cost = [0] * n  # 依次保存到每一站的最少总费用
        for i, (a, b) in enumerate(zip(regular, express), 1):  # 从第 1 站开始遍历，a、b 为两条线在第 i-1 站到第 i 站的票价
            f[i] = min(f[i - 1] + a, g[i - 1] + a)  # 只要付普通票价 a，无论上一站在哪条线都能回到普通线，取较小者
            g[i] = min(f[i - 1] + expressCost + b, g[i - 1] + b)  # 从普通线换到快线要额外付 expressCost；已在快线则只付 b
            cost[i - 1] = min(f[i], g[i])  # 两条线取较小值即为到达该站的最少费用
        return cost  # 返回每一站的最少费用列表
