# 题目：1560. 圆形赛道上经过次数最多的扇区（Most Visited Sector in a Circular Track）
# 思路：只有最后一段路径会与其他段重叠，所以经过次数最多的扇区就是最后一段覆盖的扇区；跨过 n→1 边界时拆成两段。
# 时间复杂度：O(n)，最多输出 n 个扇区；空间复杂度：O(n)，返回的列表本身。
class Solution:  # LeetCode 约定的题解类
    def mostVisited(self, n: int, rounds: List[int]) -> List[int]:  # n：扇区总数；rounds：每轮的起始扇区
        if rounds[0] <= rounds[-1]:  # 起点不大于终点，说明最后一段没有跨过 n → 1 的边界
            return list(range(rounds[0], rounds[-1] + 1))  # 未跨边界：最后一段 [起点, 终点] 就是被多走一次的扇区
        return list(range(1, rounds[-1] + 1)) + list(range(rounds[0], n + 1))  # 跨边界：把 [1, 终点] 与 [起点, n] 两段拼接成答案
