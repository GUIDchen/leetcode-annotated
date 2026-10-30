# 题目：3369. 设计数组统计跟踪器（Design an Array Statistics Tracker）
# 思路：deque 维护 FIFO 顺序，总和求均值，SortedList 按大小求中位数，另一份 SortedList 按（次数降序, 数值升序）求众数。
# 时间复杂度：增删均摊 O(log n)，三个查询均 O(1) 或 O(log n)；空间复杂度：O(n)。
class StatisticsTracker:  # 滑动窗口统计器：维护均值、中位数与众数
    def __init__(self):  # 构造函数：初始化所需的容器
        self.q = deque()  # 双端队列，按加入顺序保存元素，便于从队首移除最早加入的
        self.s = 0  # 窗口内元素总和，用于 O(1) 求均值
        self.cnt = defaultdict(int)  # 每个值的出现次数（默认 0），用于维护众数
        self.sl = SortedList()  # 有序列表，用于 O(log n) 求中位数
        self.sl2 = SortedList(key=lambda x: (-x[1], x[0]))  # 有序列表，元素为 (数值, 出现次数)，按（次数降序, 数值升序）排序，首元素即众数

    def addNumber(self, number: int) -> None:  # 加入一个新元素
        self.q.append(number)  # 追加到队尾，保持加入顺序
        self.sl.add(number)  # 插入有序列表，供中位数查询
        self.sl2.discard((number, self.cnt[number]))  # 先删掉这个数旧的 (数值, 旧次数) 记录
        self.cnt[number] += 1  # 出现次数加一
        self.sl2.add((number, self.cnt[number]))  # 按新次数重新插入，维持众数排序
        self.s += number  # 累加窗口总和

    def removeFirstAddedNumber(self) -> None:  # 移除最早加入的元素（FIFO 淘汰）
        number = self.q.popleft()  # 弹出队首元素
        self.sl.remove(number)  # 从有序列表中删掉该值
        self.sl2.discard((number, self.cnt[number]))  # 删掉它旧的 (数值, 旧次数) 记录
        self.cnt[number] -= 1  # 出现次数减一
        self.sl2.add((number, self.cnt[number]))  # 按新次数插回有序列表
        self.s -= number  # 总和减去该值

    def getMean(self) -> int:  # 当前窗口的均值（整除即向下取整）
        return self.s // len(self.q)  # 用总和除以当前元素个数

    def getMedian(self) -> int:  # 当前窗口的中位数
        return self.sl[len(self.q) // 2]  # 有序列表下标从 0 开始，取 len // 2 即下中位数，与题目定义一致

    def getMode(self) -> int:  # 当前窗口的众数
        return self.sl2[0][0]  # sl2 按（次数降序, 数值升序）排序，首元素的数值就是众数


# Your StatisticsTracker object will be instantiated and called as such:
# obj = StatisticsTracker()
# obj.addNumber(number)
# obj.removeFirstAddedNumber()
# param_3 = obj.getMean()
# param_4 = obj.getMedian()
# param_5 = obj.getMode()
