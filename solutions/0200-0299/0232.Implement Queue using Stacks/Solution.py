# 题目：232. 用栈实现队列（Implement Queue using Stacks）
# 思路：两个列表当栈，stk1 只负责入队；出队或取队首时若 stk2 为空，就把 stk1 全部倒进 stk2，顺序被翻正，stk2 末尾即队首。
# 时间复杂度：均摊 O(1)，每个元素最多被搬动一次；空间复杂度：O(n)，两个栈合计存 n 个元素。
class MyQueue:  # 用两个栈模拟队列的类
    def __init__(self):  # 构造函数：准备两个空栈
        self.stk1 = []  # 输入栈：只负责 push
        self.stk2 = []  # 输出栈：负责 pop 与 peek

    def push(self, x: int) -> None:  # 入队：x 是待入队的元素
        self.stk1.append(x)  # 直接追加到输入栈，入队 O(1)

    def pop(self) -> int:  # 出队：返回并删除队首元素
        self.move()  # 先整理两个栈，保证 stk2 非空且栈顶是队首
        return self.stk2.pop()  # 弹出并返回队首

    def peek(self) -> int:  # 取队首：只读不删
        self.move()  # 同样先整理两个栈
        return self.stk2[-1]  # stk2 的末尾元素就是队首

    def empty(self) -> bool:  # 判空
        return not self.stk1 and not self.stk2  # 两个栈都空，队列才空

    def move(self):  # 把输入栈的元素全部倒进输出栈，从而翻转元素顺序
        if not self.stk2:  # 只有输出栈为空时才搬，避免打乱已经排好的顺序
            while self.stk1:  # 逐个弹出输入栈的元素
                self.stk2.append(self.stk1.pop())  # 追加到输出栈，后进先出正好把顺序倒过来


# Your MyQueue object will be instantiated and called as such:
# obj = MyQueue()
# obj.push(x)
# param_2 = obj.pop()
# param_3 = obj.peek()
# param_4 = obj.empty()
