# 题目：1928. 规定时间内到达终点的最小花费（Minimum Cost to Reach Destination in Time）
# 思路：f[i][v] 表示恰好用 i 单位时间到达节点 v 的最小花费，按时间切面枚举每条边做松弛，最后在终点的各时间切面上取最小值。
# 时间复杂度：O(m·E)，m 为 maxTime、E 为边数；空间复杂度：O(m·n)，需要一张 (m+1)×n 的二维表。
class Solution:  # LeetCode 约定的题解类
    def minCost(  # maxTime：时间上限；edges：无向边；passingFees：每个节点的过路费
        self, maxTime: int, edges: List[List[int]], passingFees: List[int]  # 参数含义见上一行注释
    ) -> int:  # 返回规定时间内到达终点的最小花费，无法到达时返回 -1
        m, n = maxTime, len(passingFees)  # m 是时间上限，n 是节点个数
        f = [[inf] * n for _ in range(m + 1)]  # f[i][v]：恰好用 i 单位时间到达 v 的最小花费
        f[0][0] = passingFees[0]  # 0 时刻位于起点 0，花费就是起点的过路费
        for i in range(1, m + 1):  # 按时间从小到大逐个切面推进
            for x, y, t in edges:  # 遍历每条无向边，x、y 是端点，t 是耗时
                if t <= i:  # 边耗时不超过当前时间才有意义
                    f[i][x] = min(f[i][x], f[i - t][y] + passingFees[x])  # 在 i 时刻经这条边从 y 到达 x
                    f[i][y] = min(f[i][y], f[i - t][x] + passingFees[y])  # 反向同理：在 i 时刻经这条边从 x 到达 y
        ans = min(f[i][n - 1] for i in range(m + 1))  # 终点在所有时间切面上的最小花费
        return ans if ans < inf else -1  # 仍然是 inf 说明无法在 maxTime 内到达终点
