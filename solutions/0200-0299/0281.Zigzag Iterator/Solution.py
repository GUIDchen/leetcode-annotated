# 题目：281. 锯齿迭代器（Zigzag Iterator）🔒
# 思路：把两个数组都存起来，用 cur 记录当前轮到哪个数组、indexes 记录各数组已消费到的位置，每次 next 后轮转到另一个数组；hasNext 跳过已耗尽的数组。
# 时间复杂度：O(1) 均摊每次操作；空间复杂度：O(k)，只存指针与数组引用（k 为数组个数）。
class ZigzagIterator:  # 锯齿迭代器：交替遍历 v1 与 v2
    def __init__(self, v1: List[int], v2: List[int]):  # 构造函数：v1、v2 是两个待交替遍历的数组
        self.cur = 0  # 当前准备输出元素的那个数组下标
        self.size = 2  # 参与交替的数组个数
        self.indexes = [0] * self.size  # 每个数组已经消费到的位置，初始都为 0
        self.vectors = [v1, v2]  # 保存两个数组的引用，便于按下标取值

    def next(self) -> int:  # 返回下一个元素并前进，按锯齿顺序轮转
        vector = self.vectors[self.cur]  # 取出当前该遍历的数组
        index = self.indexes[self.cur]  # 该数组已消费到的位置
        res = vector[index]  # 暂存要返回的元素
        self.indexes[self.cur] = index + 1  # 该数组消费位置后移一位
        self.cur = (self.cur + 1) % self.size  # 轮转到下一个数组，取模实现首尾循环
        return res  # 返回暂存的元素

    def hasNext(self) -> bool:  # 判断是否还有元素可取
        start = self.cur  # 记录起始数组，用于检测是否已绕回一圈
        while self.indexes[self.cur] == len(self.vectors[self.cur]):  # 当前数组已耗尽就继续往后找
            self.cur = (self.cur + 1) % self.size  # 轮转到下一个数组
            if self.cur == start:  # 绕回起点说明所有数组都空了
                return False  # 确实没有更多元素
        return True  # 当前数组还有剩余元素


# Your ZigzagIterator object will be instantiated and called as such:
# i, v = ZigzagIterator(v1, v2), []
# while i.hasNext(): v.append(i.next())
