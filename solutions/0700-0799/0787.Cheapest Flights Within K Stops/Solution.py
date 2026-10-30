# 题目：787. K 站中转内最便宜的航班（Cheapest Flights Within K Stops）
# 思路：受限边数的 Bellman-Ford；迭代 k+1 轮，每轮只允许用上一轮快照 backup 再加一条边，以此恰好限制中转次数。
# 时间复杂度：O(k·m)，m 是航班数；空间复杂度：O(n)，距离数组与快照。
class Solution:  # LeetCode 约定的题解类
    def findCheapestPrice(  # 求 src 到 dst 在最多 k 次中转内的最低价格
        self, n: int, flights: List[List[int]], src: int, dst: int, k: int  # n 是城市数，flights 每项为 [起点, 终点, 价格]
    ) -> int:  # 返回最低价格，不可达时返回 -1
        INF = 0x3F3F3F3F  # 「不可达」标记，取一个足够大的常数
        dist = [INF] * n  # dist[v]：当前轮次下到达 v 的最小花费
        dist[src] = 0  # 起点到自身花费为 0
        for _ in range(k + 1):  # 最多 k 次中转，等价于最多走 k+1 条边
            backup = dist.copy()  # 冻结上一轮结果，否则本轮会连锁更新成多走边，中转次数就超了
            for f, t, p in flights:  # 枚举所有航班边，拆出起点 f、终点 t、价格 p
                dist[t] = min(dist[t], backup[f] + p)  # 只用「上一轮的 dist[f] 加一条边」来松弛 t
        return -1 if dist[dst] == INF else dist[dst]  # 不可达返回 -1，否则返回最小花费
