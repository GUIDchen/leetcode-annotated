# 3560. 木材运输的最小成本 / Find Minimum Log Transportation Cost
# 核心思路：成本只与较长的那根木头有关，若其长度超过 k 则需切下长度为 x-k 的一段，成本为 k*(x-k)，否则无需切割。
# 复杂度：时间 O(1)，空间 O(1)
class Solution:  # 定义解题类
    def minCuttingCost(self, n: int, m: int, k: int) -> int:  # 返回把两根木头切到长度都不超过 k 的最小成本
        x = max(n, m)  # 只需关注较长的那根木头
        return 0 if x <= k else k * (x - k)  # 无需切割则为 0，否则成本为 k * (x - k)
