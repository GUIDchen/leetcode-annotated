# 题目：155. 最小栈（Min Stack）
# 思路：两个列表当栈用，stk1 保存所有元素，stk2 同步保存「当前栈顶位置对应的历史最小值」，同增同减。
# 时间复杂度：push/pop/top/getMin 均为 O(1)；空间复杂度：O(n)，每个元素在两个列表中各存一份。
class MinStack:  # 题目要求实现的最小栈类
    def __init__(self):  # 构造函数：初始化两个栈
        self.stk1 = []  # 数据栈，保存所有入栈元素
        self.stk2 = [inf]  # 最小值栈，用 inf 作哨兵，保证第一次取 min 时不会出错

    def push(self, val: int) -> None:  # 入栈：两个栈同步增长
        self.stk1.append(val)  # 数据栈追加新元素
        self.stk2.append(min(val, self.stk2[-1]))  # 最小值栈追加「新元素」与「此前最小值」中的较小者，-1 取的是当前栈顶

    def pop(self) -> None:  # 出栈：两栈同步弹出，保证最小值栈栈顶对应当前数据栈的最小值
        self.stk1.pop()  # 弹出数据栈栈顶
        self.stk2.pop()  # 弹出最小值栈栈顶

    def top(self) -> int:  # 返回栈顶元素，即最后入栈的值
        return self.stk1[-1]  # 列表末尾就是栈顶

    def getMin(self) -> int:  # 返回当前栈内最小元素
        return self.stk2[-1]  # 最小值栈的末尾始终是当前最小值


# Your MinStack object will be instantiated and called as such:
# obj = MinStack()
# obj.push(val)
# obj.pop()
# param_3 = obj.top()
# param_4 = obj.getMin()
