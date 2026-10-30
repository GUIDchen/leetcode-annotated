# 题目：2285. 道路的最大总重要性（Maximum Total Importance of Roads）
# 核心思路：城市的重要性被它参与的每条道路各算一次，所以总重要性 = Σ 重要性 × 度数；让度数最大的城市拿最大的重要性即最优，排序后逐项相乘求和。
# 时间复杂度：O(E + n log n)，E 为道路数，耗时在给 n 个度数排序；空间复杂度：O(n)，保存各城市度数。
class Solution:  # LeetCode 约定的题解类
    def maximumImportance(self, n: int, roads: List[List[int]]) -> int:  # n：城市个数；roads：无向道路列表；返回最大总重要性
        deg = [0] * n  # 每个城市的度数（相连道路条数），初始为 0
        for a, b in roads:  # 遍历每条道路，两端城市度数各加 1
            deg[a] += 1  # 道路一端城市度数 +1
            deg[b] += 1  # 道路另一端城市度数 +1
        deg.sort()  # 度数升序排序，为后面「大度数配大重要性」做准备
        return sum(i * v for i, v in enumerate(deg, 1))  # enumerate 从 1 开始，给最小度数配重要性 1，逐项相乘再求和
