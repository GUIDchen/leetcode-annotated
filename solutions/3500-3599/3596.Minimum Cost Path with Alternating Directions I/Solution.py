# 3596. 交替方向的最小路径代价 I（Minimum Cost Path with Alternating Directions I）
# 核心思路：按交替方向的移动规则枚举可达规模，只有 1×1、1×2、2×1 能走到终点，直接返回对应最小代价，其余规模无解返回 -1。
# 复杂度：时间 O(1)，空间 O(1)。
class Solution:  # 主解类
    def minCost(self, m: int, n: int) -> int:  # 输入网格行列数 m、n，返回最小路径代价
        if m == 1 and n == 1:  # 只有起点一个格子
            return 1  # 最小代价就是起点的代价
        if m == 2 and n == 1:  # 2 行 1 列的唯一可行小网格
            return 3  # 代价为 3
        if m == 1 and n == 2:  # 1 行 2 列的唯一可行小网格
            return 3  # 代价为 3
        return -1  # 其余规模按交替方向规则无法到达终点
