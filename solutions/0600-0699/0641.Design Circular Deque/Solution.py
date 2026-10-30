# 题目：641. 设计循环双端队列（Design Circular Deque）
# 核心思路：用定长列表加队头下标 front 和元素个数 size 组成环形缓冲区，队尾位置由 front + size 推出；所有插入、删除都靠取模让下标绕回。
# 时间复杂度：每个操作 O(1)；空间复杂度：O(k)，存放 k 个槽位。
class MyCircularDeque:  # 循环双端队列：定长列表 + 队头下标 + 元素个数组成环形缓冲区
    def __init__(self, k: int):  # 构造：容量为 k 的双端队列
        """
        Initialize your data structure here. Set the size of the deque to be k.
        """  # 文档字符串结束，下面开始正式初始化
        self.q = [0] * k  # 长度为 k 的定长列表，循环复用
        self.front = 0  # 队头元素所在的下标
        self.size = 0  # 当前元素个数
        self.capacity = k  # 容量上限

    def insertFront(self, value: int) -> bool:  # 从队头插入元素，成功返回 True
        """
        Adds an item at the front of Deque. Return true if the operation is successful.
        """  # 文档字符串结束
        if self.isFull():  # 队列已满则无法插入
            return False  # 插入失败
        if not self.isEmpty():  # 队列非空时队头需要前移一格
            self.front = (self.front - 1 + self.capacity) % self.capacity  # 先加容量再取模，避免出现负数下标
        self.q[self.front] = value  # 把新元素写到新的队头位置
        self.size += 1  # 元素个数加一
        return True  # 插入成功

    def insertLast(self, value: int) -> bool:  # 从队尾插入元素，成功返回 True
        """
        Adds an item at the rear of Deque. Return true if the operation is successful.
        """  # 文档字符串结束
        if self.isFull():  # 队列已满则无法插入
            return False  # 插入失败
        idx = (self.front + self.size) % self.capacity  # 队尾的下一个空位下标，取模绕回
        self.q[idx] = value  # 写入新元素
        self.size += 1  # 元素个数加一
        return True  # 插入成功

    def deleteFront(self) -> bool:  # 从队头删除元素，成功返回 True
        """
        Deletes an item from the front of Deque. Return true if the operation is successful.
        """  # 文档字符串结束
        if self.isEmpty():  # 空队列没有元素可删
            return False  # 删除失败
        self.front = (self.front + 1) % self.capacity  # 队头后移一格并取模绕回
        self.size -= 1  # 元素个数减一
        return True  # 删除成功

    def deleteLast(self) -> bool:  # 从队尾删除元素，成功返回 True
        """
        Deletes an item from the rear of Deque. Return true if the operation is successful.
        """  # 文档字符串结束
        if self.isEmpty():  # 空队列没有元素可删
            return False  # 删除失败
        self.size -= 1  # 只需把个数减一，原队尾元素自然失效
        return True  # 删除成功

    def getFront(self) -> int:  # 返回队头元素
        """
        Get the front item from the deque.
        """  # 文档字符串结束
        if self.isEmpty():  # 空队列按题意返回 -1
            return -1  # 空队列的约定返回值
        return self.q[self.front]  # 返回队头元素

    def getRear(self) -> int:  # 返回队尾元素
        """
        Get the last item from the deque.
        """  # 文档字符串结束
        if self.isEmpty():  # 空队列按题意返回 -1
            return -1  # 空队列的约定返回值
        idx = (self.front + self.size - 1) % self.capacity  # 最后一个元素的下标
        return self.q[idx]  # 返回队尾元素

    def isEmpty(self) -> bool:  # 判断队列是否为空
        """
        Checks whether the circular deque is empty or not.
        """  # 文档字符串结束
        return self.size == 0  # 元素个数为 0 即为空

    def isFull(self) -> bool:  # 判断队列是否已满
        """
        Checks whether the circular deque is full or not.
        """  # 文档字符串结束
        return self.size == self.capacity  # 元素个数等于容量即为满


# Your MyCircularDeque object will be instantiated and called as such:
# obj = MyCircularDeque(k)
# param_1 = obj.insertFront(value)
# param_2 = obj.insertLast(value)
# param_3 = obj.deleteFront()
# param_4 = obj.deleteLast()
# param_5 = obj.getFront()
# param_6 = obj.getRear()
# param_7 = obj.isEmpty()
# param_8 = obj.isFull()
