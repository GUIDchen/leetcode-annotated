# 题目：1029. 两地调度（Two City Scheduling）
# 思路：按「去 A 比去 B 便宜多少」排序，让最划算去 A 的 n 人去 A、剩下 n 人去 B；该贪心可交换论证最优。
# 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(log n)，排序递归栈开销。
class Solution:  # LeetCode 约定的题解类
    def twoCitySchedCost(self, costs: List[List[int]]) -> int:  # costs[i] = [去 A 城的费用, 去 B 城的费用]；返回最小总费用
        costs.sort(key=lambda x: x[0] - x[1])  # 按「去 A 比去 B 便宜多少」升序排序，差值越小越应该去 A
        n = len(costs) >> 1  # 右移一位等价于整除 2，得到每座城市要安排的人数
        return sum(costs[i][0] + costs[i + n][1] for i in range(n))  # 前 n 人去 A（费用下标 0）、后 n 人去 B（费用下标 1），生成器求和后返回
