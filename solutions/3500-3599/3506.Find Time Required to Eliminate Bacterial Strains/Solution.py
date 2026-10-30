# 题目：3506. 查找消除细菌菌株所需时间（Find Time Required to Eliminate Bacterial Strains）
# 思路：小顶堆模拟。每轮弹出耗时最小的菌株（它必然最先被消除），再取新的堆顶加上 splitTime 放回堆中，表示这次分裂的代价累加到它身上；堆中只剩一个元素时，该值就是消除全部菌株的总时间。
# 时间复杂度：O(n log n)，每个元素进出堆各 O(log n)；空间复杂度：O(n)，堆中最多存 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def minEliminationTime(self, timeReq: List[int], splitTime: int) -> int:  # timeReq：每种菌株被消除所需时间；splitTime：一次分裂的耗时；返回消除全部菌株的总时间
        heapify(timeReq)  # 把输入列表原地整理成小顶堆
        while len(timeReq) > 1:  # 堆中多于一个菌株时继续合并
            heappop(timeReq)  # 弹出耗时最小的菌株，它会被最先消除
            heappush(timeReq, heappop(timeReq) + splitTime)  # 弹出新的堆顶，加上一次分裂耗时后重新入堆
        return timeReq[0]  # 堆顶即累计的消除时间
