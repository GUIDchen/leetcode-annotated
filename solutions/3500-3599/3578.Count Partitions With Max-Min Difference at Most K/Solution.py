# 题目：3578. 统计极差最大为 K 的分割方式数 / Count Partitions With Max-Min Difference at Most K（中等）
# 核心思路：设 f[r] 表示把前 r 个元素分割、且最后一段以 r 结尾（起点 s >= l）的方案数，g 为 f 的前缀和便于区间求和；用有序列表 SortedList 维护滑窗 [l, r] 的最大值与最小值，一旦极差超过 k 就把左边界右移，保证以 r 结尾的合法最后一段起点至少为 l，于是 f[r] = f[l-1] + ... + f[r-1] = g[r-1] - g[l-2]。
# 复杂度：时间复杂度 O(n log n)，空间复杂度 O(n)。
class Solution:  # 定义题解类
    def countPartitions(self, nums: List[int], k: int) -> int:  # 返回极差不超过 k 的分割方式数
        mod = 10**9 + 7  # 取模常数
        sl = SortedList()  # 有序列表，用于 O(log n) 维护滑窗最值
        n = len(nums)  # 数组长度
        f = [1] + [0] * n  # f[r] 为前 r 个元素的分割方案数，f[0] = 1 作为边界
        g = [1] + [0] * n  # g 为 f 的前缀和
        l = 1  # 合法最后一段起点的下界（1 基准下标）
        for r, x in enumerate(nums, 1):  # 枚举分割前缀的长度 r（从 1 开始）
            sl.add(x)  # 把新元素加入有序列表
            while sl[-1] - sl[0] > k:  # 滑窗极差超过 k
                sl.remove(nums[l - 1])  # 移出左端点对应的元素
                l += 1  # 左边界右移
            f[r] = (g[r - 1] - (g[l - 2] if l >= 2 else 0) + mod) % mod  # 最后一段起点可在 [l, r]，方案数由前缀和作差得到
            g[r] = (g[r - 1] + f[r]) % mod  # 更新前缀和
        return f[n]  # 前 n 个元素的方案数即答案
