# 3599. 划分数组得到最小 XOR（Partition Array to Minimize XOR）
# 核心思路：异或前缀和把每一段的异或转成区间异或，再做 DP：f[i][j] 表示前 i 个数分成 j 段时“各段异或最大值”的最小值。
# 复杂度：时间 O(n^2 · k)，空间 O(n · k)。
min = lambda a, b: a if a < b else b  # 自定义 min，语义与内置 min 相同
max = lambda a, b: a if a > b else b  # 自定义 max，语义与内置 max 相同


class Solution:  # 主解类
    def minXor(self, nums: List[int], k: int) -> int:  # 把数组划分成 k 段，使各段异或和中最大者尽量小
        n = len(nums)  # 数组长度
        g = [0] * (n + 1)  # 异或前缀和数组
        for i, x in enumerate(nums, 1):  # 下标从 1 开始遍历
            g[i] = g[i - 1] ^ x  # 异或前缀递推

        f = [[inf] * (k + 1) for _ in range(n + 1)]  # DP 表 f[i][j]：前 i 个数分成 j 段的最小最大值
        f[0][0] = 0  # 边界：0 个数分成 0 段，代价为 0
        for i in range(1, n + 1):  # 枚举前缀长度 i
            for j in range(1, min(i, k) + 1):  # 段数 j 不能超过元素个数 i，也不能超过 k
                for h in range(j - 1, i):  # 枚举最后一段的起点 h
                    f[i][j] = min(f[i][j], max(f[h][j - 1], g[i] ^ g[h]))  # 转移：最后一段区间异或与前面最大值取较大者，再取最小
        return f[n][k]  # 返回前 n 个数分成 k 段的最优值
