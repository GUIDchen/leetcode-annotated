# 题目：2247. K 条高速公路的最大旅行费用（Maximum Cost of Trip With K Highways，会员题）
# 思路：状压 DP，f[mask][j] 表示访问过城市集合 mask、最后停在 j 的最大费用；按 mask 递增枚举，用「去掉 j 后停在邻居 h」的状态转移。
# 时间复杂度：O(2^n * n * deg)，每个状态枚举所有邻边；空间复杂度：O(2^n * n)，DP 表与邻接表。
class Solution:  # LeetCode 约定的题解类
    def maximumCost(self, n: int, highways: List[List[int]], k: int) -> int:  # n 是城市数，highways 每条为 [a, b, cost]，k 是必须经过的高速条数
        if k >= n:  # 走 k 条边需要 k+1 个不同城市，城市不够时不可能完成
            return -1  # 无解返回 -1
        g = defaultdict(list)  # 邻接表：g[u] 中存 (相邻城市, 该高速费用)
        for a, b, cost in highways:  # 逐条高速解包出两个端点与费用
            g[a].append((b, cost))  # 无向图，正向边
            g[b].append((a, cost))  # 反向边费用相同
        f = [[-inf] * n for _ in range(1 << n)]  # f[mask][j]：访问过 mask 这些城市且最后停在 j 时的最大费用；-inf 表示不可达
        for i in range(n):  # 任意单个城市都可作为起点
            f[1 << i][i] = 0  # 只含城市 i 的路径还没走过高速，费用为 0
        ans = -1  # 答案初值 -1 表示暂时无解
        for i in range(1 << n):  # 按 mask 递增枚举所有城市集合
            for j in range(n):  # 枚举当前所在城市 j
                if i >> j & 1:  # j 必须属于 mask，否则该状态无意义
                    for h, cost in g[j]:  # 枚举 j 的邻居 h 及这条边的费用
                        if i >> h & 1:  # h 也必须已在集合中，保证转移来源合法、路径不重复经过城市
                            f[i][j] = max(f[i][j], f[i ^ (1 << j)][h] + cost)  # 把 j 从集合里去掉（i ^ (1 << j)），由停在 h 的状态加这条边的费用转移而来
                if i.bit_count() == k + 1:  # bit_count() 统计集合中城市个数：恰好 k+1 个城市即恰好 k 条高速
                    ans = max(ans, f[i][j])  # 用所有终点里的最大值更新答案
        return ans  # 返回最大费用，可能仍为 -1
