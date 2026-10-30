# 3857. 拆分到 1 的最小总代价 / Minimum Cost to Split into Ones（中等）
# 核心思路：一次拆分 a + b = x 的代价 a * b 恰好统计了本次被分到两侧的 1 的配对数，而每一对 1 最终恰好被分开一次，所以总代价与拆分顺序无关，恒为 C(n, 2)。
# 复杂度：时间 O(1)，空间 O(1)。
class Solution:  # 设计一个算法：求把 n 拆成 n 个 1 的最小总代价
    def minCost(self, n: int) -> int:  # 返回把 n 拆成 n 个 1 的最小总代价
        return n * (n - 1) // 2  # 总代价恒为 C(n, 2)：每一对 1 恰好被某一次拆分分开并贡献 1
