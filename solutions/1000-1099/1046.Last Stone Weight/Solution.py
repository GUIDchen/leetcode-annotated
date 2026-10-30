# 题目：1046. 最后一块石头的重量（Last Stone Weight）
# 思路：用大根堆反复取出最重与次重的两块石头对撞，重量相同则一起粉碎，否则把差值放回堆中，直到不足两块。
# 时间复杂度：O(n log n)，每次堆操作 O(log n)；空间复杂度：O(n)，堆最多保存 n 块石头。
class Solution:  # LeetCode 约定的题解类
    def lastStoneWeight(self, stones: List[int]) -> int:  # stones：每块石头的重量；返回最后剩下的重量
        h = [-x for x in stones]  # heapq 是小根堆，所以取负数来模拟大根堆
        heapify(h)  # O(n) 原地建堆；heapq 的函数在判题环境中已导入
        while len(h) > 1:  # 不足两块石头时停止对撞
            y, x = -heappop(h), -heappop(h)  # 依次弹出最重与次重，取负还原真实重量（y >= x）
            if x != y:  # 重量相同则两块一起粉碎，不产生新石头
                heappush(h, x - y)  # 否则把重量差（取负）放回堆中继续参与对撞
        return 0 if not h else -h[0]  # 堆空说明全部碎光返回 0，否则堆顶取负即最后一块的重量
