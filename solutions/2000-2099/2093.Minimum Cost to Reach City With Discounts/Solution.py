# 题目：2093. 前往目标城市的最小费用（Minimum Cost to Reach City With Discounts）
# 思路：把「已用折扣次数」并入状态做分层 Dijkstra，每条边扩展出「原价」与「半价且次数 +1」两个后继。
# 时间复杂度：O(m·d·log(m·d))，d = discounts，每个状态至多入堆一次；空间复杂度：O(n·d)，dist 表与堆。
class Solution:  # LeetCode 约定的题解类
    def minimumCost(self, n: int, highways: List[List[int]], discounts: int) -> int:  # n：城市数；highways：{a, b, c} 公路；discounts：可用折扣次数上限
        g = defaultdict(list)  # 邻接表：g[u] 存 (相邻城市, 过路费)
        for a, b, c in highways:  # 逐条读取公路
            g[a].append((b, c))  # 建 a -> b 的边
            g[b].append((a, c))  # 公路是无向的，再建 b -> a 的边
        q = [(0, 0, 0)]  # 堆元素为 (已花费用, 城市, 已用折扣次数)，初始只有起点
        dist = [[inf] * (discounts + 1) for _ in range(n)]  # dist[i][k]：用掉 k 次折扣到达城市 i 的最小费用，初始为无穷大
        while q:  # Dijkstra 主循环
            cost, i, k = heappop(q)  # 取出当前费用最小的状态
            if k > discounts:  # 折扣次数已超限
                continue  # 该状态无效，直接丢弃
            if i == n - 1:  # 第一次弹出终点时即为最小费用
                return cost  # 返回该费用
            if dist[i][k] > cost:  # 该状态尚未被更小的费用确认过
                dist[i][k] = cost  # 记录该状态的最优费用
                for j, v in g[i]:  # 枚举从 i 出发的每条公路
                    heappush(q, (cost + v, j, k))  # 不使用折扣：正常付费，次数不变
                    heappush(q, (cost + v // 2, j, k + 1))  # 使用一次折扣：费用减半（整除），次数加一
        return -1  # 始终到不了终点，返回 -1
