# 题目：1000. 合并石头的最低成本（Minimum Cost to Merge Stones）
# 思路：区间 DP，f[i][j][k] 表示把区间 [i, j] 合并成 k 堆的最小代价；用分界点拆成「左边 1 堆 + 右边 k-1 堆」，再单独处理把 K 堆并成 1 堆的额外代价。
# 时间复杂度：O(n^3 · K)，空间复杂度：O(n^2 · K)。
class Solution:  # LeetCode 约定的题解类
    def mergeStones(self, stones: List[int], K: int) -> int:  # stones：每堆石子数；K：每次必须合并的堆数；返回合并成 1 堆的最小总代价
        n = len(stones)  # 石子堆数
        if (n - 1) % (K - 1):  # 每次合并让堆数减少 K-1，n 堆变 1 堆要求 (n-1) 能被 K-1 整除
            return -1  # 有余数说明无解，按题意返回 -1
        s = list(accumulate(stones, initial=0))  # 前缀和：s[i] 是前 i 堆之和，initial=0 让 s[0] = 0
        f = [[[inf] * (K + 1) for _ in range(n + 1)] for _ in range(n + 1)]  # f[i][j][k]：把区间 [i, j] 合并成 k 堆的最小代价；inf 表示暂不可达
        for i in range(1, n + 1):  # 先处理长度为 1 的区间
            f[i][i][1] = 0  # 单堆区间已是 1 堆，代价为 0
        for l in range(2, n + 1):  # 按区间长度由小到大递推
            for i in range(1, n - l + 2):  # 枚举左端点，n - l + 2 保证右端点不越界
                j = i + l - 1  # 由左端点和长度算出右端点 j
                for k in range(1, K + 1):  # 枚举要合并成的堆数 k
                    for h in range(i, j):  # 枚举分界点 h，把区间拆成 [i, h] 与 [h+1, j]
                        f[i][j][k] = min(f[i][j][k], f[i][h][1] + f[h + 1][j][k - 1])  # 左半段合成 1 堆、右半段合成 k-1 堆，取总代价最小者
                f[i][j][1] = f[i][j][K] + s[j] - s[i - 1]  # 把 K 堆再并成 1 堆，额外付出的代价是整个区间的石子总数
        return f[1][n][1]  # 返回把 1..n 全部合并成 1 堆的最小代价
