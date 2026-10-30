# 题目：295. 数据流的中位数（Find Median from Data Stream）
# 思路：对顶堆——小顶堆存较大的一半，大顶堆用负数取反模拟、存较小的一半，并保持小顶堆元素数为 ⌈n/2⌉。
# 时间复杂度：addNum 为 O(log n)、findMedian 为 O(1)；空间复杂度：O(n)，两个堆共存 n 个数。
class MedianFinder:  # 数据流中位数：用两个堆把数据分成较小、较大两半

    def __init__(self):  # 初始化两个堆
        self.minq = []  # 小顶堆：存较大的一半元素
        self.maxq = []  # 大顶堆：存较小的一半，这里用负数取反来模拟

    def addNum(self, num: int) -> None:  # num：新加入数据流的数
        heappush(self.minq, -heappushpop(self.maxq, -num))  # 先把 -num 压入大顶堆再弹出其最小（即较小一半的最大值），取反后送入小顶堆
        if len(self.minq) - len(self.maxq) > 1:  # 平衡条件：小顶堆最多比大顶堆多 1 个元素
            heappush(self.maxq, -heappop(self.minq))  # 超出时把小顶堆堆顶取反挪回大顶堆

    def findMedian(self) -> float:  # 返回当前数据流的中位数
        if len(self.minq) == len(self.maxq):  # 两堆等长说明总数是偶数
            return (self.minq[0] - self.maxq[0]) / 2  # maxq 里存的是相反数，所以用减法还原中间两数的平均
        return self.minq[0]  # 否则多出的元素在小顶堆堆顶，直接返回


# Your MedianFinder object will be instantiated and called as such:
# obj = MedianFinder()
# obj.addNum(num)
# param_2 = obj.findMedian()
