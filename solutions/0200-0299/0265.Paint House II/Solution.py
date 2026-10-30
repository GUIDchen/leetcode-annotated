# 题目：265. 粉刷房子 II（Paint House II）
# 思路：f[j] 表示最后一间房刷颜色 j 的最小累计花费；换到下一间房时，加上上一行除 j 外的最小值。
# 时间复杂度：O(n·k²)；空间复杂度：O(k)，用两行滚动数组代替 n×k 的表。
class Solution:  # LeetCode 约定的题解类
    def minCostII(self, costs: List[List[int]]) -> int:  # costs[i][j] 是把第 i 间房刷成颜色 j 的花费
        n, k = len(costs), len(costs[0])  # n 为房子数，k 为颜色数
        f = costs[0][:]  # f 保存第 0 间房各颜色的花费，用切片复制以免改动原数组
        for i in range(1, n):  # 从第 1 间房开始逐行递推
            g = costs[i][:]  # g 是当前行的花费副本，同样复制后累加
            for j in range(k):  # 枚举当前房子要刷的颜色 j
                t = min(f[h] for h in range(k) if h != j)  # 上一行不能选同色，所以只从 h != j 的颜色中取最小值
                g[j] += t  # 当前颜色的总花费 = 本行花费 + 上一行除 j 外的最小花费
            f = g  # 用本行结果替换上一行，实现原地滚动
        return min(f)  # 最后一间房可以是任意颜色，取最小值即为答案
