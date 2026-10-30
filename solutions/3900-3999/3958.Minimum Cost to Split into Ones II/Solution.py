# 题目：3958. 拆分到 1 的最小总代价 II（Minimum Cost to Split into Ones II）
# 思路：从 1 开始自底向上合并到 n，第 k 步把长度 k 与剩下的 1 合并需 k 次操作，总代价为 1+2+...+(n-1)。
# 复杂度：时间 O(1)，空间 O(1)。
class Solution:  # LeetCode 约定的题解类
    def minCost(self, n: int) -> int:  # n 是待拆分的整数
        return n * (n - 1) // 2  # 总代价 = 1+2+...+(n-1) = n(n-1)/2
