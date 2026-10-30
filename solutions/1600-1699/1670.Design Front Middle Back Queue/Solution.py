# 题目：1670. 设计前中后队列（Design Front Middle Back Queue）
# 思路：用两个双端队列把队列切成前后两半，始终保持 len(q1) <= len(q2) <= len(q1) + 1，中位元素自然落在两半交界处。
# 时间复杂度：每次操作 O(1)；空间复杂度：O(n)，两个 deque 合计存 n 个元素。
class FrontMiddleBackQueue:  # 两个双端队列维护前后两半：q1 是前半，q2 是后半
    def __init__(self):  # 构造函数
        self.q1 = deque()  # 前半部分，队首即整个队列的队首
        self.q2 = deque()  # 后半部分，队尾即整个队列的队尾

    def pushFront(self, val: int) -> None:  # 在队首插入 val
        self.q1.appendleft(val)  # 队首元素归入前半 q1
        self.rebalance()  # 调整两半长度，恢复平衡约束

    def pushMiddle(self, val: int) -> None:  # 在队列正中间插入 val
        self.q1.append(val)  # 先放到前半末尾，再由 rebalance 决定是否挪到后半
        self.rebalance()  # 调整两半长度，让 val 落在中位

    def pushBack(self, val: int) -> None:  # 在队尾插入 val
        self.q2.append(val)  # 队尾元素归入后半 q2
        self.rebalance()  # 调整两半长度，恢复平衡约束

    def popFront(self) -> int:  # 弹出并返回队首元素，队空时返回 -1
        if not self.q1 and not self.q2:  # 两个队列都空即整个队列为空
            return -1  # 按题意返回 -1
        if self.q1:  # 前半非空时，队首一定在 q1
            val = self.q1.popleft()  # 从 q1 队首弹出
        else:  # 前半为空，队首落在 q2 的头部
            val = self.q2.popleft()  # 从 q2 队首弹出
        self.rebalance()  # 删除后重新平衡两半长度
        return val  # 返回弹出的值

    def popMiddle(self) -> int:  # 弹出并返回正中间元素，队空时返回 -1
        if not self.q1 and not self.q2:  # 整体为空，按题意返回 -1
            return -1  # 返回 -1
        if len(self.q1) == len(self.q2):  # 两半等长时，中位是前半的最后一个元素
            val = self.q1.pop()  # 从 q1 尾部弹出
        else:  # 否则 q2 比 q1 多一个，中位是 q2 的队首
            val = self.q2.popleft()  # 从 q2 队首弹出
        self.rebalance()  # 删除后重新平衡
        return val  # 返回弹出的值

    def popBack(self) -> int:  # 弹出并返回队尾元素，队空时返回 -1
        if not self.q2:  # 队尾一定在 q2，q2 为空即整体为空
            return -1  # 按题意返回 -1
        val = self.q2.pop()  # 从 q2 尾部弹出
        self.rebalance()  # 删除后重新平衡
        return val  # 返回弹出的值

    def rebalance(self):  # 维持 len(q1) <= len(q2) <= len(q1) + 1
        if len(self.q1) > len(self.q2):  # 前半过长，把它的尾元素挪到后半的头部
            self.q2.appendleft(self.q1.pop())  # q1 尾元素出队，随即从 q2 头部入队
        if len(self.q2) > len(self.q1) + 1:  # 后半比前半多一个以上，把它的头元素挪到前半的尾部
            self.q1.append(self.q2.popleft())  # q2 头元素出队，随即从 q1 尾部入队


# Your FrontMiddleBackQueue object will be instantiated and called as such:
# obj = FrontMiddleBackQueue()
# obj.pushFront(val)
# obj.pushMiddle(val)
# obj.pushBack(val)
# param_4 = obj.popFront()
# param_5 = obj.popMiddle()
# param_6 = obj.popBack()
