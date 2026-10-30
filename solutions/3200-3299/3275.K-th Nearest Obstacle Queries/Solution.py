# 题目：3275. 第 K 近障碍物查询（K-th Nearest Obstacle Queries）
# 思路：用小根堆（Python 里存负数模拟）维护当前最近的 k 个曼哈顿距离，堆顶就是第 k 近的距离。
# 时间复杂度：O(q log k)，每个查询入堆、出堆各一次；空间复杂度：O(k)，堆中最多保留 k 个元素。
class Solution:  # LeetCode 约定的题解类
    def resultsArray(self, queries: List[List[int]], k: int) -> List[int]:  # queries：障碍物坐标；k：查询的是第 k 近
        ans = []  # 保存每个查询的答案
        pq = []  # 小根堆（实际存负数），只保留当前最近的 k 个距离
        for i, (x, y) in enumerate(queries):  # i 是已加入障碍物的下标，从 0 开始
            heappush(pq, -(abs(x) + abs(y)))  # 存入曼哈顿距离的相反数，用大根堆模拟小根堆
            if i >= k:  # 堆中元素已经超过 k 个
                heappop(pq)  # 弹出（负数意义下）最大的，也就是实际最远的那个
            ans.append(-pq[0] if i >= k - 1 else -1)  # 凑够 k 个时返回第 k 近，否则返回 -1
        return ans  # 返回所有查询的答案
