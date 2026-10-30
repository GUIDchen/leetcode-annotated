# 题目：2558. 从数量最多的堆取走礼物（Take Gifts From the Richest Pile）
# 思路：Python 只有小根堆，把礼物数量取相反数入堆模拟大根堆；每次用 heapreplace 弹出堆顶、开平方取整后放回，重复 k 次，最后对相反数求和再取反。
# 时间复杂度：O(n + k log n)，建堆 O(n)，每次替换 O(log n)；空间复杂度：O(n)，堆数组 h。
class Solution:  # LeetCode 约定的题解类
    def pickGifts(self, gifts: List[int], k: int) -> int:  # gifts 是每堆礼物的数量，k 是操作次数
        h = [-v for v in gifts]  # 取相反数把“最大”变成“最小”，这样小根堆的堆顶就是数量最多的那堆
        heapify(h)  # 原地建堆
        for _ in range(k):  # 重复 k 次操作
            heapreplace(h, -int(sqrt(-h[0])))  # 弹出堆顶、开平方取整后放回，一步完成（-h[0] 还原真实值）
        return -sum(h)  # 堆里存的是相反数，求和后取反得到真实总和
