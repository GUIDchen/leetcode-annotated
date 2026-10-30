# 题目：1959. K 次调整数组大小浪费的最小总空间（Minimum Total Space Wasted With K Resizing Operations）
# 思路：至多 k 次调整等于把数组切成至多 k+1 段、每段共用一个容量；预处理每段浪费 g[i][j]，再对「前 i 个元素分 j 段」做区间 DP。
# 时间复杂度：O(n^2·k)；空间复杂度：O(n^2 + n·k)，分别存放区间浪费表与 DP 表。
class Solution:  # LeetCode 约定的题解类
    def minSpaceWastedKResizing(self, nums: List[int], k: int) -> int:  # nums 是各阶段的元素个数，k 是允许调整大小的次数
        k += 1  # k 次调整等价于把数组切成至多 k+1 段，段内共用一个容量
        n = len(nums)  # 元素个数
        g = [[0] * n for _ in range(n)]  # g[i][j]：把 nums[i..j] 当作一段（同一容量）时的浪费空间
        for i in range(n):  # 枚举段左端点
            s = mx = 0  # s 是段内元素和，mx 是段内最大值（该段所需的最小容量）
            for j in range(i, n):  # 从 i 开始向右逐渐扩展本段
                s += nums[j]  # 先累加元素和
                mx = max(mx, nums[j])  # 同时维护最大值，保证容量不低于段内任何元素
                g[i][j] = mx * (j - i + 1) - s  # 容量 × 段长 − 实际占用 = 浪费
        f = [[inf] * (k + 1) for _ in range(n + 1)]  # f[i][j]：前 i 个元素分 j 段的最小浪费；inf 是内建的 float('inf')，无需 import
        f[0][0] = 0  # 边界：0 个元素、0 段，浪费为 0
        for i in range(1, n + 1):  # 逐渐扩大已处理的前缀
            for j in range(1, k + 1):  # 枚举已使用的段数
                for h in range(i):  # 枚举最后一段的起点 h
                    f[i][j] = min(f[i][j], f[h][j - 1] + g[h][i - 1])  # 状态松弛：前 h 个元素分 j-1 段 + 最后一段 [h, i) 的浪费
        return f[-1][-1]  # 等价于 f[n][k]，即分成至多 k+1 段的最小浪费
