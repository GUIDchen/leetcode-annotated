# 题目：1615. 最大网络秩（Maximal Network Rank）
# 思路：先统计每个城市的度数 cnt，再用邻接矩阵 g 标记直连关系；枚举所有城市对，秩 = cnt[a] + cnt[b] - g[a][b]。
# 时间复杂度：O(n^2 + m)，m 为道路条数；空间复杂度：O(n^2)，主要开销是邻接矩阵。
class Solution:  # LeetCode 约定的题解类
    def maximalNetworkRank(self, n: int, roads: List[List[int]]) -> int:  # n：城市个数；roads：道路端点列表
        g = [[0] * n for _ in range(n)]  # 邻接矩阵：g[a][b] == 1 表示 a、b 之间有一条直接道路
        cnt = [0] * n  # cnt[i] 表示与城市 i 直接相连的道路条数（度数）
        for a, b in roads:  # 遍历每条道路
            g[a][b] = g[b][a] = 1  # 无向图，对称位置都置 1，供后面减去重复道路
            cnt[a] += 1  # 端点 a 的度数加一
            cnt[b] += 1  # 端点 b 的度数加一
        return max(cnt[a] + cnt[b] - g[a][b] for a in range(n) for b in range(a + 1, n))  # 枚举所有无序城市对取最大秩
