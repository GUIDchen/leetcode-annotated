# 题目：622. 设计循环队列（Design Circular Queue）
# 思路：定长数组 + 队头下标 + 元素个数；入队写在下标 (front+size)%capacity，出队后移 front，用 size 区分空与满。
# 时间复杂度：每个操作均为 O(1)；空间复杂度：O(k)，需要一个容量为 k 的定长数组。
class MyCircularQueue:  # 用定长数组加队头下标实现的循环队列
    def __init__(self, k: int):  # 构造函数，k 为队列容量
        self.q = [0] * k  # 申请 k 个槽位并全部初始化为 0
        self.size = 0  # 当前元素个数；用它可以避免「队头=队尾」时无法区分空与满
        self.capacity = k  # 记录容量 k，取模时要用
        self.front = 0  # 队头元素在数组中的下标

    def enQueue(self, value: int) -> bool:  # 入队：成功返回 True，队满返回 False
        if self.isFull():  # 已满则无法入队
            return False  # 入队失败
        self.q[(self.front + self.size) % self.capacity] = value  # 队尾下标 = 队头 + 元素个数，取模后自然绕回数组开头
        self.size += 1  # 元素个数加一
        return True  # 入队成功

    def deQueue(self) -> bool:  # 出队：成功返回 True，队空返回 False
        if self.isEmpty():  # 已空则无法出队
            return False  # 出队失败
        self.front = (self.front + 1) % self.capacity  # 队头后移一格并取模，走到末尾就绕回开头
        self.size -= 1  # 元素个数减一
        return True  # 出队成功

    def Front(self) -> int:  # 取队头元素，空队列返回 -1
        return -1 if self.isEmpty() else self.q[self.front]  # 条件表达式：空队列返回 -1，否则返回队头槽位的值

    def Rear(self) -> int:  # 取队尾元素，空队列返回 -1
        if self.isEmpty():  # 空队列按题目约定返回 -1
            return -1  # 返回 -1 作为空队列的标记
        return self.q[(self.front + self.size - 1) % self.capacity]  # 队尾下标 = 队头 + 元素个数 - 1，取模后就是队尾槽位

    def isEmpty(self) -> bool:  # 判空：元素个数为 0
        return self.size == 0  # size 为 0 即空队列

    def isFull(self) -> bool:  # 判满：元素个数等于容量
        return self.size == self.capacity  # size 达到容量即已满


# 下面是 LeetCode 判题器自动生成的对象使用示例注释，原样保留
# Your MyCircularQueue object will be instantiated and called as such:
# obj = MyCircularQueue(k)
# param_1 = obj.enQueue(value)
# param_2 = obj.deQueue()
# param_3 = obj.Front()
# param_4 = obj.Rear()
# param_5 = obj.isEmpty()
# param_6 = obj.isFull()
