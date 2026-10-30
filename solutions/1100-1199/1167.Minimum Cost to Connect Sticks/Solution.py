# 题目：1167. 连接木棍的最低费用（Minimum Cost to Connect Sticks）
# 思路：贪心 + 小根堆，每次合并最短的两根，合并代价为新长度并累加，新木棍再放回堆中继续合并。
# 时间复杂度：O(n log n)，每轮都要出堆两次再入堆一次；空间复杂度：O(n)，堆中最多保存 n 根木棍。
class Solution:  # 题解类
    def connectSticks(self, sticks: List[int]) -> int:  # 把木棍两两连接成一根，返回最小总费用
        heapify(sticks)  # 原地建小根堆，方便每次取最短的两根
        ans = 0  # 累计总费用
        while len(sticks) > 1:  # 堆中只剩一根木棍时结束
            z = heappop(sticks) + heappop(sticks)  # 弹出最短的两根合并，z 既是新木棍长度也是本次花费
            ans += z  # 累加本次费用
            heappush(sticks, z)  # 新木棍放回堆中继续参与合并
        return ans  # 返回最小总费用
