# 题目：225. 用队列实现栈（Implement Stack using Queues）
# 思路：push 时先把新元素放进辅助队列 q2，再把 q1 的旧元素整体搬到 q2 尾部，最后交换两队列，让 q1 的左端始终是栈顶。
# 时间复杂度：push 为 O(n)（要搬动全部元素），pop/top/empty 为 O(1)；空间复杂度：O(n)，两个队列共存 n 个元素。
class MyStack:  # 只用队列模拟出的栈
    def __init__(self):  # 构造函数：建两个空双端队列当队列用
        self.q1 = deque()  # q1 保存全部元素，左端是栈顶
        self.q2 = deque()  # q2 只在 push 时临时使用

    def push(self, x: int) -> None:  # 入栈：x 是待压入的元素
        self.q2.append(x)  # 新元素先入 q2，它将成为新的栈顶
        while self.q1:  # 把 q1 里已有的元素按原顺序全部搬到 q2 尾部
            self.q2.append(self.q1.popleft())  # 从 q1 左端取出并追加到 q2 右端
        self.q1, self.q2 = self.q2, self.q1  # 交换引用后 q1 持有完整数据，q2 变回空队列

    def pop(self) -> int:  # 出栈：q1 左端就是栈顶，弹出并返回
        return self.q1.popleft()  # popleft 对应队列出队，同时完成删除

    def top(self) -> int:  # 返回栈顶元素但不删除
        return self.q1[0]  # 下标 0 即 q1 左端，也就是栈顶

    def empty(self) -> bool:  # 判断栈是否为空
        return len(self.q1) == 0  # 队列长度为 0 等价于栈为空


# Your MyStack object will be instantiated and called as such:
# obj = MyStack()
# obj.push(x)
# param_2 = obj.pop()
# param_3 = obj.top()
# param_4 = obj.empty()
