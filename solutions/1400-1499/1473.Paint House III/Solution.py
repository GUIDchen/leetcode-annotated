# 题目：1473. 粉刷房子 III（Paint House III）
# 思路：三维 DP，f[i][j][k] 表示刷完前 i+1 个房子、第 i 个房子颜色为 j、且恰好形成 k 个颜色街区时的最小花费。
# 时间复杂度：O(m * n^2 * target)，空间复杂度：O(m * n * target)。
class Solution:  # LeetCode 约定的题解类
    def minCost(  # houses：各房子颜色（0 表示待刷）；cost：刷色价格；m：房子数；n：颜色数；target：目标街区数
        self, houses: List[int], cost: List[List[int]], m: int, n: int, target: int  # 参数列表（换行写法沿用原文件）
    ) -> int:  # 返回最小总花费，无解时返回 -1
        f = [[[inf] * (target + 1) for _ in range(n + 1)] for _ in range(m)]  # DP 表：颜色 1..n、街区数 1..target，多留一位哨兵
        if houses[0] == 0:  # 第一个房子未刷，可以任意选色
            for j, c in enumerate(cost[0], 1):  # 枚举第一个房子的颜色 j 与对应价格 c
                f[0][j][1] = c  # 只有 1 个街区，花费即刷色价格
        else:  # 第一个房子已有固定颜色
            f[0][houses[0]][1] = 0  # 颜色固定、街区数为 1、额外花费为 0
        for i in range(1, m):  # 从第二个房子开始逐个转移
            if houses[i] == 0:  # 当前房子未刷，需要枚举颜色
                for j in range(1, n + 1):  # 枚举当前房子的颜色 j
                    for k in range(1, min(target + 1, i + 2)):  # 枚举街区数 k；最多 i+1 个街区，最多只关心到 target
                        for j0 in range(1, n + 1):  # 枚举前一个房子的颜色 j0
                            if j == j0:  # 同色，街区数不增加
                                f[i][j][k] = min(  # 取「继承上一房子花费 + 本次刷色价格」的较小值
                                    f[i][j][k], f[i - 1][j][k] + cost[i][j - 1]  # 上一房子同为颜色 j、街区数同为 k
                                )
                            else:  # 异色，街区数加一
                                f[i][j][k] = min(  # 从 k-1 个街区的状态转移过来
                                    f[i][j][k], f[i - 1][j0][k - 1] + cost[i][j - 1]  # 上一房子颜色为 j0、街区数为 k-1
                                )
            else:  # 当前房子已有固定颜色，不必枚举颜色
                j = houses[i]  # 当前房子被固定的颜色
                for k in range(1, min(target + 1, i + 2)):  # 枚举街区数 k
                    for j0 in range(1, n + 1):  # 枚举前一个房子的颜色 j0
                        if j == j0:  # 同色，街区数不变
                            f[i][j][k] = min(f[i][j][k], f[i - 1][j][k])  # 不花钱，直接继承
                        else:  # 异色，街区数加一
                            f[i][j][k] = min(f[i][j][k], f[i - 1][j0][k - 1])  # 从 k-1 个街区转移

        ans = min(f[-1][j][target] for j in range(1, n + 1))  # 最后一个房子颜色任选，取街区数恰为 target 的最小花费
        return -1 if ans >= inf else ans  # 仍是无穷大说明无解，返回 -1
