# 题目：2959. 关闭分部的可行集合数目（Number of Possible Sets of Closing Branches）
# 思路：枚举要保留的分部集合（二进制掩码），只保留两端都保留的道路并跑 Floyd，最后用 all 判断所有保留点对的距离是否都不超过 maxDistance。
# 时间复杂度：O(2^n * n^3)，每种集合做一次 Floyd；空间复杂度：O(n^2)，每轮新建一个 n×n 的距离矩阵。
class Solution:  # LeetCode 约定的题解类
    def numberOfSets(self, n: int, maxDistance: int, roads: List[List[int]]) -> int:  # n 为分部数，maxDistance 为距离上限，roads 为道路列表
        ans = 0  # 记录可行方案数
        for mask in range(1 << n):  # 枚举 2^n 个保留集合，mask 的第 k 位为 1 表示保留分部 k
            g = [[inf] * n for _ in range(n)]  # 距离矩阵，初始为无穷大（inf 由判题环境提供）
            for u, v, w in roads:  # 遍历每条道路
                if mask >> u & 1 and mask >> v & 1:  # 只有两端分部都保留时才能走这条道路
                    g[u][v] = min(g[u][v], w)  # 无向边取较小权重，处理重边
                    g[v][u] = min(g[v][u], w)  # 反方向做同样的赋值
            for k in range(n):  # Floyd 的中间点 k
                if mask >> k & 1:  # 中间点必须属于保留集合
                    g[k][k] = 0  # 自己到自己的距离为 0
                    for i in range(n):  # 枚举起点 i
                        for j in range(n):  # 枚举终点 j
                            # g[i][j] = min(g[i][j], g[i][k] + g[k][j])  # 原文件的注释保留不动，说明这里原本是直接写 min 的版本
                            if g[i][k] + g[k][j] < g[i][j]:  # 经过 k 的路径更短则松弛
                                g[i][j] = g[i][k] + g[k][j]  # 更新 i 到 j 的最短路
            if all(  # 判断该集合下所有保留点对是否都满足距离上限
                g[i][j] <= maxDistance  # 点对 (i, j) 的距离不超过上限
                for i in range(n)  # 枚举起点
                for j in range(n)  # 枚举终点
                if mask >> i & 1 and mask >> j & 1  # 只检查两端都被保留的点对
            ):  # all 为真说明当前集合可行
                ans += 1  # 可行方案数加一
        return ans  # 返回可行方案总数
