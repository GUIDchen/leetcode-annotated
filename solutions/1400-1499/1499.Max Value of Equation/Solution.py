# 题目：1499. 满足不等式的最大值（Max Value of Equation）
# 思路：把目标式改写成 (x+y) + (y'-x')，用小根堆存 -(y'-x') 以维护窗口内 y'-x' 最大的点，过期就弹出。
# 时间复杂度：O(n log n)，每个点进出堆各一次；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def findMaxValueOfEquation(self, points: List[List[int]], k: int) -> int:  # 在 |x_i - x_j| <= k 的点对中最大化 y_i + y_j + |x_i - x_j|
        ans = -inf  # 答案初始化为负无穷（题目保证至少有一对）
        pq = []  # 小根堆，存 (-(y-x), x)，堆顶就是 y-x 最大的点
        for x, y in points:  # 按 x 升序处理每个点
            while pq and x - pq[0][1] > k:  # 堆顶点与当前点距离超过 k，已经过期
                heappop(pq)  # 弹出过期点
            if pq:  # 堆里还有合法点
                ans = max(ans, x + y - pq[0][0])  # 化简为 (x+y) - (x'-y')，pq[0][0] 存的是 -(y'-x')，所以直接相减
            heappush(pq, (x - y, x))  # 当前点入堆，存入负的 (y-x) 以适配小根堆
        return ans  # 返回最大值
