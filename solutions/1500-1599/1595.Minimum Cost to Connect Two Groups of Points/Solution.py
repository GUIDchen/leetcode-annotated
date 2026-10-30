# 题目：1595. 连通两组点的最小成本（Minimum Cost to Connect Two Groups of Points）
# 思路：状压 DP，f[i][j] 表示前 i 个第一组点、第二组已连边集合为 j 时的最小成本，逐点用三种来源转移。
# 时间复杂度：O(m * n * 2^n)，枚举点、集合与第二组的点；空间复杂度：O(m * 2^n)，保存每层每个集合的最优值。
class Solution:  # LeetCode 约定的题解类
    def connectTwoGroups(self, cost: List[List[int]]) -> int:  # cost[i][j] 是两组点之间的连接代价
        m, n = len(cost), len(cost[0])  # m 为第一组点数，n 为第二组点数
        f = [[inf] * (1 << n) for _ in range(m + 1)]  # f[i][j]：前 i 个点已处理、第二组已连边集合为 j 的最小成本
        f[0][0] = 0  # 边界：没有点也没连边时成本为 0
        for i in range(1, m + 1):  # 逐个加入第一组的第 i 个点
            for j in range(1 << n):  # 枚举第二组的已连边集合（状压）
                for k in range(n):  # 枚举这个点连向第二组的哪一个点
                    if (j >> k & 1) == 0:  # k 不在集合 j 中，这条转移不合法
                        continue  # 跳过这种连法
                    c = cost[i - 1][k]  # 第 i 个点连向 k 的代价（下标从 0 开始）
                    x = min(f[i][j ^ (1 << k)], f[i - 1][j], f[i - 1][j ^ (1 << k)]) + c  # 三种来源取最小后加上本轮代价：本层已含 k、上一层已含 j 再连 k、上一层集合少 k
                    f[i][j] = min(f[i][j], x)  # 用较小值更新当前状态
        return f[m][-1]  # 全部点处理完且第二组点全部连上边时的答案
