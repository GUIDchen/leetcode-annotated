# 题目：1962. 移除石子使总数最小（Remove Stones to Minimize the Total）
# 思路：贪心——每次都对当前最大的一堆做「移除一半」，用负数加小顶堆模拟大顶堆取最大值。
# 时间复杂度：O((n + k) log n)；空间复杂度：O(n)，堆中保存所有石子堆。
class Solution:  # LeetCode 约定的题解类
    def minStoneSum(self, piles: List[int], k: int) -> int:  # piles 是每堆石子数，k 是最多操作次数
        pq = [-x for x in piles]  # Python 只有小顶堆，取负数即可模拟大顶堆
        heapify(pq)  # 原地把列表调整成合法的小顶堆
        for _ in range(k):  # 重复 k 次操作，_ 表示不使用循环变量
            heapreplace(pq, pq[0] // 2)  # 弹出堆顶并用 pq[0] // 2 替换再重新堆化；负数下恰好等价于原值 x 变为 x - x//2
        return -sum(pq)  # 取负还原后求和，即为剩余石子总数
